//Use argc and argv for file input via command line. If argc>1 use file input, and if argc=0 use command line input. 

#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

double GetRad(double deg);
double GetDeltaLat(double x, double currentLat);
double GetDeltaLon(double x, double currentLat);
void ExportData(vector<double> latitude, vector<double> longitude, vector<double> altitude);

int main()
{
	const double METER_PER_MILE = 1609.34;
	const double METER_PER_FOOT = 0.3048;
	const double SECOND_PER_HOUR = 3600;
	const double METER_SECOND_PER_KNOT = 0.514444;
	double terminalVelocity;
	double lastKnownLatitude;
	double lastKnownLongitude;
	double lastKnownAltitude;
	double lastKnownVelocity;
	double lastKnownHeading;
	double tempVelocity;
	double tempHeading;
	double tempAltitude;
	double deltaTime;
	double deltaX;
	double deltaY;
	vector<double> latitude;
	vector<double> longitude;
	vector<double> altitude;
	vector<double> velocity;
	vector<double> heading;

	//Prompt for units

	//command line input starts here
	//Prompt for initial position
	cout << "Enter last known position as follows:\n"
		 << "<Latitude[degrees]> <Longitude[degrees]> <Altitude[m relative to ground]>" << endl;
	cin >> lastKnownLatitude >> lastKnownLongitude >> lastKnownAltitude;
	cout << endl;

	//pushback vectors with initial position
	latitude.push_back(lastKnownLatitude);
	longitude.push_back(lastKnownLongitude);
	altitude.push_back(lastKnownAltitude);

	//prompt for last known relevant information
	cout << "Enter last known velocity (relative to ground), heading, and terminal velocity as follows:\n"
		 << "<Heading[degrees west of north]> <Velocity[m/s]> <terminal velocity[m/s]>" << endl;
	cin >> lastKnownHeading >> lastKnownVelocity >> terminalVelocity;
	cout << endl;

	//pushback initial values for said information
	heading.push_back(lastKnownHeading);
	velocity.push_back(lastKnownVelocity);

	//Prompt for wind data
	cout << "Using data below the last known point, enter wind data\n"
	     << "(from Bufkit or something) as follows. Finish with CTRL-Z:\n"
		 << "<heading[degrees west of north]> <velocity[m/s]> <altitude[m above ground]>" << endl;

	//retrieve wind data and pushback vectors
	while (cin >> tempHeading)
	{
		cin >> tempVelocity >> tempAltitude;

		heading.push_back(tempHeading);
		velocity.push_back(tempVelocity);
		altitude.push_back(tempAltitude);
	}
	cout << endl;
	//end input via command line

	//Do calculation for subsequent positions
	cout << "----------\nPath:" << endl;
	for (unsigned int i = 0; i < altitude.size() - 1; ++i)
	{
		deltaTime = fabs((altitude[i + 1] - altitude[i]) / terminalVelocity);
		deltaY = deltaTime * velocity[i] * cos(GetRad(heading[i]));//change in x in meters (change in longitude)
		deltaX = deltaTime * velocity[i] * sin(GetRad(heading[i]));//change in y in meters (change in latitude)
		latitude.push_back(GetDeltaLat(deltaY, latitude[i]) + latitude[i]);
		longitude.push_back(GetDeltaLon(deltaX, latitude[i]) + longitude[i]);

		cout << latitude[i] << " " << longitude[i] << " " << altitude[i] << endl;
	}

	cout << "\n----------\n" << endl;
	cout << "Payload's predicted location is..." << endl;
	cout << latitude.back() << " deg.lat, " << longitude.back() << " deg.lon, at " << altitude.back() << " m.\n" << endl;

	ExportData(latitude, longitude, altitude);

	cout << "Done." << endl;
	return 0;
}


double GetRad(double deg)
{
	return deg * M_PI / 180.0;
}


double GetDeltaLat(double x, double currentLat)
{
	double term1 = 559.82 * cos(2 * GetRad(currentLat));
	double term2 = 1.175 * cos(4 * GetRad(currentLat));
	double term3 = 0.0023 * cos(6 * GetRad(currentLat));
	double deltaLat = (x / (111132.92 - term1 + term2 - term3));

	return deltaLat;
}


double GetDeltaLon(double y, double currentLat)
{
	double term1 = 111412.84 * cos(GetRad(currentLat));
	double term2 = 93.5 * cos(3 * GetRad(currentLat));
	double term3 = 0.118 * cos(5 * GetRad(currentLat));
	double deltaLon = (y / (term1 - term2 + term3));

	return deltaLon;
}


void ExportData(vector<double> latitude, vector<double> longitude, vector<double> altitude)
{
	ofstream kml("extrap.kml");
	kml << fixed << setprecision(8);
	
	//kml header
	kml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
		<< "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"
		<< "<Document>\n"
		<< "<name>Extrapolation</name>\n"
		<< "<description>Created by LG's Program</description>\n" << endl;

	//set line style
	kml << "<Style id=\"yellowPoly\">\n"
		<< "<LineStyle>\n"
		<< "<color>7f00ffff</color>\n"
		<< "<width>4</width>\n"
		<< "</LineStyle>\n"
		<< "<PolyStyle>\n"
		<< "<color>7f00ff00</color>\n"
		<< "</PolyStyle>\n"
		<< "</Style>\n" << endl;

	//set line path
	kml << "<Placemark>\n"
		<< "<name>Flight Extrapolation</name>\n"
		<< "<description>Extrap by LG's Program</description>\n"
		<< "<styleURL>#yellowPoly</styleURL>\n"
		<< "<LineString>\n"
		<< "<extrude>1</extrude>\n"
		<< "<tesselate>1</tesselate>\n"
		<< "<altitudeMode>relativeToGround</altitudeMode>\n"
		<< "<coordinates>" << endl;

	for (unsigned int i = 0; i < altitude.size(); ++i)
	{
		kml << longitude[i] << "," << latitude[i] << "," << altitude[i] << endl;
	}

	kml << "</coordinates>\n"
		<< "</LineString>\n"
		<< "</Placemark>\n" << endl;

	//kml footer
	kml << "</Document>\n"
		<< "</kml>" << endl;

	kml.close();
}