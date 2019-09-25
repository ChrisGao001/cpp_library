// refer https://juejin.im/post/5c32a1c26fb9a049b13e5bdf
public class RingBuffer<T> {
    private volatile T[] elements;
    private volatile int head;
    private volatile int tail;

    public RingBuffer(int capacity){
        this.elements=(T[])new Object[capacity];
        this.head=0;
        this.tail=-1;
    }

    private boolean isEmpty(){
        return tail+1==head;
    }

    private boolean isFull(){
        return tail+1-elements.length==head;
    }

    public void push(T element) throws IllegalArgumentException{
        if(isFull())
            throw new IllegalArgumentException("full queue");
        elements[(tail+1)%elements.length]=element;
        tail++;
    }

    public T pop() throws IllegalArgumentException{
        if(isEmpty())
            throw new IllegalArgumentException("empty queue");
        T element=elements[head%elements.length];
        head++;
        return element;
    }
}

