/*
Please read 5.groovy first
Here we will see how to execute conditional statements. */

def amPM = Calendar.getInstance().get(Calendar.AM_PM);
if(amPM == Calendar.AM) {
	println "Good Morning"
}
else {
	println "Good Evening"
}


