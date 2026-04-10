public class MonitorContador {
    private int contador;

    public MonitorContador(int inicial) {
        this.contador = inicial;
    }

    public synchronized int getContador() {
        return contador;
    }

    public synchronized void esperarCambio(Thread thread) {

        //*  TO DO

        try {
            System.out.println("[" + thread.getName() + "]: Dormido en espera pasiva");
            wait();
            System.out.println("[" + thread.getName() + "]: Despierto. Cambio detectado: " + (contador + 1) + " -> " + contador);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public synchronized void decrementarYNotificar(Thread thread) {

        //* TO DO

        contador--;
        System.out.println("[" + thread.getName() + "]: Contador decrementado a " + contador);
        notify();
    }
}
