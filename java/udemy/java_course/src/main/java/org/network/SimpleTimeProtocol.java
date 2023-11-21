package org.network;

// SimpleDaytimeProtocol

/*
create client socket to connect to time.nist.gov at port 37 and get the current time as the number of seconds since midnight (GMT), January 1, 1900.
Convert that time to the current system timezone and display on terminal
 */

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.Calendar;
import java.util.Date;
import java.util.TimeZone;

public class SimpleTimeProtocol {
    private static final String HOSTNAME = "time.nist.gov";
    private static final int PORT = 37;

    private static Date getDateTime(InputStream in) {
        long secondsSince1900 = 0;
        try {
            for (int i = 0; i < 4; ++i) {
                secondsSince1900 = (secondsSince1900 << 8) | in.read();
            }

            TimeZone gmt = TimeZone.getTimeZone("GMT");

            Calendar epoch1900 = Calendar.getInstance(gmt);
            epoch1900.set(1900, Calendar.JANUARY, 1, 0, 0, 0);
            long epoch1900ms = epoch1900.getTime().getTime();

            Calendar epoch1970 = Calendar.getInstance(gmt);
            epoch1970.set(1970, Calendar.JANUARY, 1, 0, 0, 0);
//            long epoch1970ms = epoch1970.getTime().getTime();
            long epoch1970ms = epoch1970.getTimeInMillis();

            long diffSecs = (epoch1970ms - epoch1900ms)/1000;
            System.out.println("Diff in epochs between 1900 and 1970: " + diffSecs); // should be around 2208988800L

            long secondsSince1970 = secondsSince1900 - diffSecs;
            long msSince1970 = secondsSince1970 * 1000;
            return new Date(msSince1970);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        try (Socket socket = new Socket(HOSTNAME, PORT)) {
            socket.setSoTimeout(15000);
            var stream = socket.getInputStream();
            var date = getDateTime(stream);
            System.out.println("Time according to NTP protocol: " + date);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}

/*
SimpleClientReadWrite.java next
 */