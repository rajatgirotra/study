/*
 * Please read Arrays2.java first
 */
import com.rajatgirotra.util.*;
import java.util.*;

public class Collections2 {
	public static void fill (Collection c, Generator gen, int count) {
		for(int i = 0; i < count; ++i) {
			c.add(gen.next());
		}
	}
	
	public static void fill(Map m, MapGenerator gen, int count) {
		for(int i = 0; i < count; ++i) {
			Pair p = gen.next();
			m.put(p.key, p.value);
		}
	}
	
	public static class RandStringPairGenerator implements MapGenerator {
		private Arrays2.RandStringGenerator gen;
		
		public RandStringPairGenerator(int len) {
			gen = new Arrays2.RandStringGenerator(len);
		}
		
		public Pair next() {
			return new Pair(gen.next(), gen.next());
		}
	}
	
	public static RandStringPairGenerator rsp = new RandStringPairGenerator(10);
	
	public static class StringPairGenerator implements MapGenerator {
		private int index = -1;
		private String[][] data;
		public Pair next() {
			index = (index+1) % data.length;
			return new Pair(data[index][0], data[index][1]);
		}
		
		public StringPairGenerator(String[][] d) {
			data = d;
		}
		
		public StringPairGenerator reset() {
			index = -1;
			return this;
		}
	}
	
	public static StringPairGenerator geography = new StringPairGenerator(CountryCapitals.pairs);
	
	public static class StringGenerator implements Generator {
		int position;
		int index = -1;
		String[][] d;
		
		public StringGenerator(String[][] data, int pos) {
			d = data;
			position = pos;
		}
		public Object next() {
			index = (index+1) % d.length;
			return d[index][position];
		}
		
		public StringGenerator reset() {
			index = -1;
			return this;
		}
	}
	
	public static StringGenerator countries = new StringGenerator(CountryCapitals.pairs, 0);
	public static StringGenerator capitals = new StringGenerator(CountryCapitals.pairs, 1);
}

class CountryCapitals {
	public static final String[][] pairs = new String[][] { 
		// Africa
		{"ALGERIA","Algiers"}, {"ANGOLA","Luanda"},
		{"BENIN","Porto-Novo"}, {"BOTSWANA","Gaberone"},
		{"BURKINA FASO","Ouagadougou"},
		{"BURUNDI","Bujumbura"},
		{"CAMEROON","Yaounde"}, {"CAPE VERDE","Praia"},
		{"CENTRAL AFRICAN REPUBLIC","Bangui"},
		{"CHAD","N'djamena"}, {"COMOROS","Moroni"},
		{"CONGO","Brazzaville"}, {"DJIBOUTI","Dijibouti"},
		{"EGYPT","Cairo"}, {"EQUATORIAL GUINEA","Malabo"},
		{"ERITREA","Asmara"}, {"ETHIOPIA","Addis Ababa"},
		{"GABON","Libreville"}, {"THE GAMBIA","Banjul"},
		{"GHANA","Accra"}, {"GUINEA","Conakry"},
		{"GUINEA","-"}, {"BISSAU","Bissau"},
		{"COTE D'IVOIR (IVORY COAST)","Yamoussoukro"},
		{"KENYA","Nairobi"}, {"LESOTHO","Maseru"},
		{"LIBERIA","Monrovia"}, {"LIBYA","Tripoli"},
		{"MADAGASCAR","Antananarivo"}, {"MALAWI","Lilongwe"},
		{"MALI","Bamako"}, {"MAURITANIA","Nouakchott"},
		{"MAURITIUS","Port Louis"}, {"MOROCCO","Rabat"},
		{"MOZAMBIQUE","Maputo"}, {"NAMIBIA","Windhoek"},
		{"NIGER","Niamey"}, {"NIGERIA","Abuja"},
		{"RWANDA","Kigali"},
		{"SAO TOME E PRINCIPE","Sao Tome"},
		{"SENEGAL","Dakar"}, {"SEYCHELLES","Victoria"},
		{"SIERRA LEONE","Freetown"}, {"SOMALIA","Mogadishu"},
		{"SOUTH AFRICA","Pretoria/Cape Town"},
		{"SUDAN","Khartoum"},
		{"SWAZILAND","Mbabane"}, {"TANZANIA","Dodoma"},
		{"TOGO","Lome"}, {"TUNISIA","Tunis"},
		{"UGANDA","Kampala"},
		{"DEMOCRATIC REPUBLIC OF THE CONGO (ZAIRE)",
		"Kinshasa"},
		{"ZAMBIA","Lusaka"}, {"ZIMBABWE","Harare"},
		// Asia
		{"AFGHANISTAN","Kabul"}, {"BAHRAIN","Manama"},
		{"BANGLADESH","Dhaka"}, {"BHUTAN","Thimphu"},
		{"BRUNEI","Bandar Seri Begawan"},
		{"CAMBODIA","Phnom Penh"},
		{"CHINA","Beijing"}, {"CYPRUS","Nicosia"},
		{"INDIA","New Delhi"}, {"INDONESIA","Jakarta"},
		{"IRAN","Tehran"}, {"IRAQ","Baghdad"},
		{"ISRAEL","Tel Aviv"}, {"JAPAN","Tokyo"},
		{"JORDAN","Amman"}, {"KUWAIT","Kuwait City"},
		{"LAOS","Vientiane"}, {"LEBANON","Beirut"},
		{"MALAYSIA","Kuala Lumpur"}, {"THE MALDIVES","Male"},
		{"MONGOLIA","Ulan Bator"},
		{"MYANMAR (BURMA)","Rangoon"},
		{"NEPAL","Katmandu"}, {"NORTH KOREA","P'yongyang"},
		{"OMAN","Muscat"}, {"PAKISTAN","Islamabad"},
		{"PHILIPPINES","Manila"}, {"QATAR","Doha"},
		{"SAUDI ARABIA","Riyadh"}, {"SINGAPORE","Singapore"},
		{"SOUTH KOREA","Seoul"}, {"SRI LANKA","Colombo"},
		{"SYRIA","Damascus"},
		{"TAIWAN (REPUBLIC OF CHINA)","Taipei"},
		{"THAILAND","Bangkok"}, {"TURKEY","Ankara"},
		{"UNITED ARAB EMIRATES","Abu Dhabi"},
		{"VIETNAM","Hanoi"}, {"YEMEN","Sana'a"},
		// Australia and Oceania
		{"AUSTRALIA","Canberra"}, {"FIJI","Suva"},
		{"KIRIBATI","Bairiki"},
		{"MARSHALL ISLANDS","Dalap-Uliga-Darrit"},
		{"MICRONESIA","Palikir"}, {"NAURU","Yaren"},
		{"NEW ZEALAND","Wellington"}, {"PALAU","Koror"},
		{"PAPUA NEW GUINEA","Port Moresby"},
		{"SOLOMON ISLANDS","Honaira"}, {"TONGA","Nuku'alofa"},
		{"TUVALU","Fongafale"}, {"VANUATU","< Port-Vila"},
		{"WESTERN SAMOA","Apia"},
		// Eastern Europe and former USSR
		{"ARMENIA","Yerevan"}, {"AZERBAIJAN","Baku"},
		{"BELARUS (BYELORUSSIA)","Minsk"},
		{"GEORGIA","Tbilisi"},
		{"KAZAKSTAN","Almaty"}, {"KYRGYZSTAN","Alma-Ata"},
		{"MOLDOVA","Chisinau"}, {"RUSSIA","Moscow"},
		{"TAJIKISTAN","Dushanbe"}, {"TURKMENISTAN","Ashkabad"},
		{"UKRAINE","Kyiv"}, {"UZBEKISTAN","Tashkent"},
		// Europe
		{"ALBANIA","Tirana"}, {"ANDORRA","Andorra la Vella"},
		{"AUSTRIA","Vienna"}, {"BELGIUM","Brussels"},
		{"BOSNIA","-"}, {"HERZEGOVINA","Sarajevo"},
		{"CROATIA","Zagreb"}, {"CZECH REPUBLIC","Prague"},
		{"DENMARK","Copenhagen"}, {"ESTONIA","Tallinn"},
		{"FINLAND","Helsinki"}, {"FRANCE","Paris"},
		{"GERMANY","Berlin"}, {"GREECE","Athens"},
		{"HUNGARY","Budapest"}, {"ICELAND","Reykjavik"},
		{"IRELAND","Dublin"}, {"ITALY","Rome"},
		{"LATVIA","Riga"}, {"LIECHTENSTEIN","Vaduz"},
		{"LITHUANIA","Vilnius"}, {"LUXEMBOURG","Luxembourg"},
		{"MACEDONIA","Skopje"}, {"MALTA","Valletta"},
		{"MONACO","Monaco"}, {"MONTENEGRO","Podgorica"},
		{"THE NETHERLANDS","Amsterdam"}, {"NORWAY","Oslo"},
		{"POLAND","Warsaw"}, {"PORTUGAL","Lisbon"},
		{"ROMANIA","Bucharest"}, {"SAN MARINO","San Marino"},
		{"SERBIA","Belgrade"}, {"SLOVAKIA","Bratislava"},
		{"SLOVENIA","Ljujiana"}, {"SPAIN","Madrid"},
		{"SWEDEN","Stockholm"}, {"SWITZERLAND","Berne"},
		{"UNITED KINGDOM","London"}, {"VATICAN CITY","---"},
		// North and Central America
		{"ANTIGUA AND BARBUDA","Saint John's"},
		{"BAHAMAS","Nassau"},
		{"BARBADOS","Bridgetown"}, {"BELIZE","Belmopan"},
		{"CANADA","Ottawa"}, {"COSTA RICA","San Jose"},
		{"CUBA","Havana"}, {"DOMINICA","Roseau"},
		{"DOMINICAN REPUBLIC","Santo Domingo"},
		{"EL SALVADOR","San Salvador"},
		{"GRENADA","Saint George's"},
		{"GUATEMALA","Guatemala City"},
		{"HAITI","Port-au-Prince"},
		{"HONDURAS","Tegucigalpa"}, {"JAMAICA","Kingston"},
		{"MEXICO","Mexico City"}, {"NICARAGUA","Managua"},
		{"PANAMA","Panama City"}, {"ST. KITTS","-"},
		{"NEVIS","Basseterre"}, {"ST. LUCIA","Castries"},
		{"ST. VINCENT AND THE GRENADINES","Kingstown"},
		{"UNITED STATES OF AMERICA","Washington, D.C."},
		// South America
		{"ARGENTINA","Buenos Aires"},
		{"BOLIVIA","Sucre (legal)/La Paz(administrative)"},
		{"BRAZIL","Brasilia"}, {"CHILE","Santiago"},
		{"COLOMBIA","Bogota"}, {"ECUADOR","Quito"},
		{"GUYANA","Georgetown"}, {"PARAGUAY","Asuncion"},
		{"PERU","Lima"}, {"SURINAME","Paramaribo"},
		{"TRINIDAD AND TOBAGO","Port of Spain"},
		{"URUGUAY","Montevideo"}, {"VENEZUELA","Caracas"},
		};
	}


/*
Please read Collection1.java next
*/