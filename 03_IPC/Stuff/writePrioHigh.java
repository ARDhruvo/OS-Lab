import java.util.concurrent.Semaphore;

class ReadWrite{
    private Semaphore w;          // Controls write access
    private Semaphore m;           // Protects readCount
    private Semaphore writeRequest; // Writers queue here
    private int readCount;
    private int writeCount;
    
    public ReadWrite(){
        w = new Semaphore(1);
        m = new Semaphore(1);
        writeRequest = new Semaphore(1);
        readCount = 0;
        writeCount = 0;
    }
    
    public void read(String readerName) throws InterruptedException{
        // Writers have priority - if a writer is waiting, readers wait
        writeRequest.acquire();
        
        m.acquire();
        readCount++;
        if(readCount == 1) {
            w.acquire(); // First reader locks writers out
        }
        m.release();
        
        writeRequest.release(); // Allow other readers/writers to proceed
        
        // Reading
        System.out.println(readerName + " is reading");
        Thread.sleep(1000);
        System.out.println(readerName + " has finished reading");
        
        m.acquire();
        readCount--;
        if(readCount == 0) {
            w.release(); // Last reader allows writers in
        }
        m.release();
    }
    
    public void write(String writerName) throws InterruptedException{
        writeRequest.acquire(); // Writers get priority access
        w.acquire(); // Exclusive write access
        
        // Writing
        System.out.println(writerName + " is writing");
        Thread.sleep(1000);
        System.out.println(writerName + " has finished writing");
        
        w.release();
        writeRequest.release();
    }
}