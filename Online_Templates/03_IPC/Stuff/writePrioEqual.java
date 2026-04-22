import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;

class ReadWrite{
    private Semaphore w;
    private Semaphore m;
    private int readCount;
    private ReentrantLock serviceLock; // Ensures fair access
    
    public ReadWrite(){
        w = new Semaphore(1);
        m = new Semaphore(1);
        readCount = 0;
        serviceLock = new ReentrantLock(true); // Fair lock
    }
    
    public void read(String readerName) throws InterruptedException{
        serviceLock.lock(); // Ensures fair queuing with writers
        try {
            m.acquire();
            readCount++;
            if(readCount == 1) {
                w.acquire();
            }
            m.release();
        } finally {
            serviceLock.unlock();
        }
        
        // Reading
        System.out.println(readerName + " is reading");
        Thread.sleep(1000);
        System.out.println(readerName + " has finished reading");
        
        m.acquire();
        readCount--;
        if(readCount == 0) {
            w.release();
        }
        m.release();
    }
    
    public void write(String writerName) throws InterruptedException{
        serviceLock.lock(); // Same queue as readers
        try {
            w.acquire();
        } finally {
            serviceLock.unlock();
        }
        
        // Writing
        System.out.println(writerName + " is writing");
        Thread.sleep(1000);
        System.out.println(writerName + " has finished writing");
        
        w.release();
    }
}