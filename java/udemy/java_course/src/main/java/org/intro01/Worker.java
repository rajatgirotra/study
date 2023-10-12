package org.intro01;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.Duration;
import java.time.LocalDate;
import java.time.Period;
import java.time.temporal.ChronoUnit;
import java.time.temporal.TemporalUnit;
import java.util.Date;

public class Worker {
    private String name;
    private String birthDate;
    protected String endDate;

    public Worker() {

    }
    public Worker(String name, String birthDate) {
        this.name = name;
        this.birthDate = birthDate;
    }

    public int getAge() {
        LocalDate now = LocalDate.now();
        LocalDate birth = LocalDate.parse(this.birthDate);
        long res = birth.until(now, ChronoUnit.YEARS);
        return (int)res;
    }

    public double collectPay() {
        return 0.;
    }

    public void terminate(String endDate) {
        this.endDate = endDate;
    }

    @Override
    public String toString() {
        return "Worker{" +
                "name='" + name + '\'' +
                ", birthDate='" + birthDate + '\'' +
                ", endDate='" + endDate + '\'' +
                '}';
    }
}
