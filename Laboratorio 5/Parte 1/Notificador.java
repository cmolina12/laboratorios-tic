public class Notificador extends Thread {
    private MonitorContador monitor;
    private long intervalo;

    public Notificador(String nombre, MonitorContador monitor, long intervalo) {
        super(nombre);
        this.monitor = monitor;
        this.intervalo = intervalo;
    }

    @Override
    public void run() {
        while (monitor.getContador() > 0) {
            try {
                Thread.sleep(intervalo);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            monitor.decrementarYNotificar(this);
        }
        System.out.println("[" + this.getName() + "]: Finalizado");
    }
}
