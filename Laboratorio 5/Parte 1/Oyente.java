public class Oyente extends Thread {
    private MonitorContador monitor;

    public Oyente(String nombre, MonitorContador monitor) {
        super(nombre);
        this.monitor = monitor;
    }

    @Override
    public void run() {
        System.out.println("[" + this.getName() + "]: Iniciado. Valor inicial = " + monitor.getContador());
        while (monitor.getContador() > 0) {
            monitor.esperarCambio(this);
        }
        System.out.println("[" + this.getName() + "]: Finalizado");
    }
}
