class PrintableCharStack extends CharStack
{
  public PrintableCharStack(int capacity)
  {
     super(capacity);
  }

  public void printStackElements()
  {
     while(!isEmpty())
     {
       System.out.print(pop());
     }
     System.out.println();
  }
}

