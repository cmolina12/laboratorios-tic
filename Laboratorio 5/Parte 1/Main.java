public class Main {
    public static void main(String[] args) {
        System.out.println("=== EJEMPLO DE ESPERA PASIVA CON MONITOR ===\n");

        MonitorContador monitor = new MonitorContador(5);

        Thread oyente = new Oyente("Oyente", monitor);
        Thread notificador = new Notificador("Notificador", monitor, 2000);

        oyente.start();
        notificador.start();

        try {
            notificador.join();
            oyente.join();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }

        System.out.println("\n=== PROGRAMA TERMINADO ===");
    }
}

/*
 * ======================= RESPUESTAS A LAS PREGUNTAS =======================
 *
 *
 * 1. ¿Qué hace exactamente el hilo Oyente cuando llama al método esperarCambio()?
 *    ¿En qué estado queda?
 *
 *    Al llamar esperarCambio(), el Oyente adquiere el candado del objeto MonitorContador
 *    (porque el método es synchronized). Luego ejecuta wait(), lo cual: (1) libera el
 *    candado del monitor para que otros hilos puedan usarlo, (2) coloca al Oyente en la
 *    cola de espera (wait set) del monitor, y (3) el hilo pasa al estado WAITING.
 *    En este estado está completamente bloqueado y NO consume CPU, está dormido
 *    esperando a que otro hilo llame a notify() sobre el mismo monitor. Cuando el
 *    Notificador invoca notify(), el Oyente sale de WAITING, pasa a BLOCKED mientras
 *    compite por readquirir el candado, y una vez lo obtiene continúa ejecutándose
 *    justo después del wait().
 *
 * 2. ¿Qué ocurre con el hilo Oyente si se elimina la llamada a notify() dentro del
 *    método decrementarYNotificar()?
 *
 *    El Notificador sigue decrementando el contador normalmente y eventualmente termina
 *    cuando el contador llega a 0. Sin embargo, el Oyente queda en estado WAITING
 *    indefinidamente porque nadie lo despierta, nunca recibe la señal de notify().
 *    El programa nunca termina: el hilo main queda bloqueado en oyente.join() esperando
 *    a que el Oyente finalice, pero este está dormido para siempre en wait(). Esto es
 *    un deadlock parcial: sin notify(), el wait() no tiene forma de saber que la
 *    condición cambió.
 *
 * 3. ¿Qué ocurriría si en vez de notify() se usara notifyAll() en
 *    decrementarYNotificar()? ¿Habría alguna diferencia en este caso?
 *    ¿Qué pasaría si hubiera más de un oyente?
 *
 *    En este caso con un solo Oyente no hay diferencia funcional: notify() despierta
 *    al único hilo en la cola de espera, y notifyAll() haría exactamente lo mismo.
 *    Pero si hubiera múltiples oyentes esperando en wait() sobre el mismo monitor,
 *    notify() solo despertaría a uno (elegido arbitrariamente por la JVM), dejando
 *    a los demás dormidos en WAITING. Con notifyAll(), todos los oyentes serían
 *    despertados y competirían por readquirir el candado, cada uno ejecutaría
 *    secuencialmente al obtenerlo y verificaría el nuevo valor del contador.
 *    Con múltiples oyentes, notifyAll() es la opción correcta para que todos se
 *    enteren del cambio.
 *
 * 4. ¿Por qué los métodos de la clase MonitorContador están declarados como synchronized?
 *
 *    (a) Exclusión mutua: los métodos acceden y modifican la variable compartida "contador"
 *        desde múltiples hilos. Sin synchronized habría condiciones de carrera donde el
 *        Oyente podría leer un valor inconsistente mientras el Notificador lo modifica.
 *    (b) Requisito técnico de wait/notify: wait() y notify() solo pueden invocarse cuando
 *        el hilo posee el candado del objeto (dentro de un contexto synchronized). Si se
 *        llaman fuera, Java lanza IllegalMonitorStateException. El synchronized garantiza
 *        que el hilo tiene el candado antes de llamar a wait() o notify().
 *
 * 5. ¿Qué podría ocurrir si se elimina synchronized de esperarCambio() y se ejecuta
 *    el programa?
 *
 *    Al ejecutar wait() sin poseer el candado del objeto, Java lanza
 *    IllegalMonitorStateException en tiempo de ejecución, porque wait() necesita liberar
 *    el candado que el hilo posee y si no lo posee la operación es inválida. El hilo
 *    Oyente terminaría abruptamente con la excepción. Además, sin synchronized no hay
 *    garantía de visibilidad de memoria entre hilos (Java Memory Model): el Oyente
 *    podría no ver las actualizaciones del contador hechas por el Notificador, ya que
 *    cada hilo podría estar trabajando con su propia copia en caché del valor.
 */