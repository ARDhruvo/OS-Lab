import java.util.concurrent.Semaphore;

class ProducerConsumer{
    private Semaphore empty;
    private Semaphore full;
    private Semaphore mutex;
    private int[] buffer;
    private int size , in = 0 , out = 0 ;
    
    
    public ProducerConsumer(int size){
        this.size = size;
        buffer = new int[size];
        empty = new Semaphore(size);// all slots empty
        full = new Semaphore(0); // no items initally
        mutex = new Semaphore(1); // mutual exclusion
        
        
    }
    
    public void produce(int item) throws InterruptedException{
        
       empty.acquire();
       mutex.acquire();
       
       //Producing...
       buffer[in] = item;
       System.out.println("Produce: "+item);
       in = (in +1)%size;
       
       mutex.release();
       full.release();
        
    }
    
    public void consume() throws InterruptedException{
        
        full.acquire();
        mutex.acquire();
        
        //consuming....
        int item = buffer[out];
        System.out.println("Consumed: "+ item);
        
        mutex.release();
        empty.release();
    }
}

class Producer extends Thread{
    private ProducerConsumer pc;
    
    public Producer(ProducerConsumer pc){
        this.pc = pc;
        
    }
    
    @Override
    public void run(){
        int item = 1;
        try{
            while(true){
                pc.produce(item++);
                Thread.sleep(1000); //Sleep before reading again
            }
        }catch(InterruptedException e){
            e.printStackTrace();
        }
    }
}

class Consumer extends Thread{
    private ProducerConsumer pc;
    
    public Consumer(ProducerConsumer pc){
        this.pc = pc;
        
    }
    
    @Override
    public void run(){
        try{
            while(true){
                pc.consume();
                Thread.sleep(1000); //Sleep before reading again
            }
        }catch(InterruptedException e){
            e.printStackTrace();
        }
    }
}

public class Main
{
	public static void main(String[] args) {
		ProducerConsumer pc = new ProducerConsumer(5);
		
		Producer p1 = new Producer(pc);
		Consumer c1 = new Consumer(pc);
		
		p1.start();
		c1.start();
}
}