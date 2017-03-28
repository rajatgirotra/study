package del;

public class Parcel {
	public Destination getDestination(final String str) {
		return new Destination() {
			private String s;
			{
				s = str;
			}
			public String readLabel() {
				return s;
			}
			
			public String toString() {
				return s;
			}
		};
		
	}
	
	public Contents getContents(int value) {
		class PContents implements Contents {
			int value;
			PContents(int value) {
				this.value = value;
			}
			
			public int value() {
				return value;
			}
			
			public String toString() {
				return Integer.toString(value);
			}
		}
		return new PContents(value);
	}
	
	public static void main(String[] args) {
		Parcel p = new Parcel();
		Contents c = p.getContents(23);
		Destination d = p.getDestination("Amsterdam");
		System.out.println("Shipping " + c + " to " + d);
	}
}
