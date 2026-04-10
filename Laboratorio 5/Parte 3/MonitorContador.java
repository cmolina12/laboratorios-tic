public class MonitorContador {
    private volatile int contador;

    public MonitorContador(int inicial) {
        this.contador = inicial;
    }

    public int getContador() {
        return contador;
    }

    public synchronized void decrementar(Thread thread) {
        contador--;
        System.out.println("[" + thread.getName() + "]: Contador decrementado a " + contador);
    }
}