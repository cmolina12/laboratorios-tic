public class Oyente extends Thread {
    private MonitorContador monitor;

    public Oyente(String nombre, MonitorContador monitor) {
        super(nombre);
        this.monitor = monitor;
    }

    @Override
    public void run() {
        System.out.println("[" + this.getName() + "]: Iniciado. Valor inicial = " + monitor.getContador());
        int valorAnterior = monitor.getContador();
        while (valorAnterior > 0) {
            // Espera semi-activa: verifica pero cede el procesador
            while (monitor.getContador() == valorAnterior) {
                Thread.yield(); // Cede la CPU a otros hilos
            }
            int nuevoValor = monitor.getContador();
            System.out.println("[" + this.getName() + "]: Cambio detectado: " + valorAnterior + " -> " + nuevoValor);
            valorAnterior = nuevoValor;
        }
        System.out.println("[" + this.getName() + "]: Finalizado");
    }
}