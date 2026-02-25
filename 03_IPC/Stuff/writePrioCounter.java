import java.util.concurrent.Semaphore;

class ReadWrite{
    private Semaphore w;
    private Semaphore m;
    private Semaphore r; // Controls reader access when writers waiting
    private int readCount;
    private int writersWaiting;
    
    public ReadWrite(){
        w = new Semaphore(1);
        m = new Semaphore(1);
        r = new Semaphore(1);
        readCount = 0;
        writersWaiting = 0;
    }
    
    public void read(String readerName) throws InterruptedException{
        // If any writers are waiting, readers must wait
        r.acquire();
        r.release(); // Just check, don't hold
        
        m.acquire();
        readCount++;
        if(readCount == 1) {
            w.acquire();
        }
        m.release();
        
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
        m.acquire();
        writersWaiting++;
        m.release();
        
        r.acquire(); // Block new readers
        w.acquire(); // Wait for current readers to finish
        
        // Writing
        System.out.println(writerName + " is writing");
        Thread.sleep(1000);
        System.out.println(writerName + " has finished writing");
        
        w.release();
        r.release();
        
        m.acquire();
        writersWaiting--;
        m.release();
    }
}