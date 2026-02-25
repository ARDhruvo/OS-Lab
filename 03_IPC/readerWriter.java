import java.util.concurrent.Semaphore;

class ReadWrite{
    private Semaphore w;
    private Semaphore m;
    private int readCount;
    
    public ReadWrite(){
        w = new Semaphore(1);
        m = new Semaphore(1);
        readCount = 0;
    }
    
    public void read(String readerName) throws InterruptedException{
        
        m.acquire();//reader down kore dise
        
        readCount++;
        if(readCount==1)//jokhon write korte parbe na
        {
            w.acquire();//writer down kore dise
        }
        
        m.release();// reader starts reading access diye dise
        
        //Reading 
        System.out.println(readerName+" is reading");
        Thread.sleep(1000); //Simulating read time 
        System.out.println(readerName+" Has finished reading");
        
        m.acquire();

        readCount--;
        if(readCount==0)//jokhon write korte parbe
        {
            w.release(); // write korar access diye disi
        }
        m.release();
        
    }
    
    public void write(String writerName) throws InterruptedException{
        
        w.acquire(); // seme down kore disi
        
        //Writting 
        System.out.println(writerName+" is Writting");
        Thread.sleep(1000); //Simulating Write time 
        System.out.println(writerName+" Has finished Writting");
        
        w.release(); // seme up kore disi
    }
}

class Reader extends Thread{
    private ReadWrite readWrite;
    private String readerName;
    
    public Reader(ReadWrite readWrite,String readerName){
        this.readWrite = readWrite;
        this.readerName = readerName;
    }
    
    @Override
    public void run(){
        try{
            while(true){
                readWrite.read(readerName);
                Thread.sleep(1000); //Sleep before reading again
            }
        }catch(InterruptedException e){
            e.printStackTrace();
        }
    }
}

class Writer extends Thread{
    private ReadWrite readWrite;
    private String writerName;
    
    public Writer(ReadWrite readWrite,String writerName){
        this.readWrite = readWrite;
        this.writerName = writerName;
    }
    
    @Override
    public void run(){
        try{
            while(true){
                readWrite.write(writerName);
                Thread.sleep(2000); //Sleep before writting again
            }
        }catch(InterruptedException e){
            e.printStackTrace();
        }
    }
}

public class Main
{
	public static void main(String[] args) {
		ReadWrite readWrite = new ReadWrite();
		
		Reader reader1 = new Reader(readWrite , "Reader 1");
		Reader reader2 = new Reader(readWrite , "Reader 2");
		Reader reader3 = new Reader(readWrite , "Reader 3");
		Reader reader4 = new Reader(readWrite , "Reader 4");
		
		Writer writer1 = new Writer(readWrite , "Writer 1");
		Writer writer2 = new Writer(readWrite , "Writer 2");
		Writer writer3 = new Writer(readWrite , "Writer 3");
		
		reader1.start();
		reader2.start();
		reader3.start();
		reader4.start();
		writer1.start();
		writer2.start();
		writer3.start();
	}
}