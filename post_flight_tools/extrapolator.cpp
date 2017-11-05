//Use argc and argv for file input via command line. If argc>1 use file input, and if argc=0 use command line input. 

#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;

double GetRad(double deg);
double GetDeltaLat(double x, double currentLat);
double GetDeltaLon(double x, double currentLat);
double GetHumanData(vector<double> &latitude, vector<double> &longitude, vector<double> &altitude, vector<double> &velocity, vector<double> &heading);
double GetFileData(vector<double> &latitude, vector<double> &longitude, vector<double> &altitude, vector<double> &velocity, vector<double> &heading, char source[]);
void Extrapolate(vector<double> &latitude, vector<double> &longitude, vector<double> &altitude, vector<double> &velocity, vector<double> &heading, double terminalVelocity);
void ExportData(vector<double> &latitude, vector<double> &longitude, vector<double> &altitude);

int main(int argc, char *argv[])
{
	char humanData[3] = "-h";
	char fileData[3] = "-f";
	char source[21];
	char destination[21];
	double terminalVelocity;
	vector<double> latitude;
	vector<double> longitude;
	vector<double> altitude;
	vector<double> velocity;
	vector<double> heading;

	//Prompt for units

	if (argc == 2 && strcmp(argv[1],humanData) == 0)
	{
		terminalVelocity = GetHumanData(latitude, longitude, altitude, velocity, heading);
	}
	else if (argc > 2 && strcmp(argv[1], fileData) == 0)
	{
		strncpy(source, argv[2],20);
		if (argc > 3)
		{
			strncpy(destination, argv[2], 20);
		}
		terminalVelocity = GetFileData(latitude, longitude, altitude, velocity, heading, source);
	}
	else
	{
		cout << "Usage:" << endl;
		cout << "\t-h" << "     " << "input data via keyboard." << endl;
		cout << "\t\tE.g. extropolate -h <return>" << endl;
		cout << "\t-f" << "     " << "input data via file." << endl;
		cout << "\t\tmust be accompanied by source file, destination optional" << endl;
		cout << "\t\tE.g. extrapolate -f source <return>" << endl;
		cout << "\t\tE.g. extrapolate -f source destination <return>" << endl;
		return 1;
	}

	Extrapolate(latitude, longitude, altitude, velocity, heading, terminalVelocity);

	cout << "Payload's predicted location is..." << endl;
	cout << latitude.back() << " deg.lat, " << longitude.back() << " deg.lon, at " << altitude.back() << " m.\n" << endl;

	ExportData(latitude, longitude, altitude);

	cout << "Done." << endl;
	return 0;
}


double GetHumanData(vector<double> &latitude, vector<double> &longitude, vector<double> &altitude, vector<double> &velocity, vector<double> &heading)
{
	double lastKnownLatitude;
	double lastKnownLongitude;
	double terminalVelocity;
	double lastKnownHeading;
	double lastKnownVelocity;
	double lastKnownAltitude;
	double tempHeading;
	double tempVelocity;
	double tempAltitude;

	cout << "Enter last known position as follows:\n"
		<< "<Latitude[degrees]> <Longitude[degrees]> <Descent rate [m/s]>" << endl;
	cin >> lastKnownLatitude >> lastKnownLongitude >> terminalVelocity;

	cout << endl;
	cout << "Enter last known velocity (relative to ground), heading, and last known altitude:\n"
		<< "<Heading[degrees west of north]> <Velocity[m/s]> <altitude>" << endl;

	cin >> lastKnownHeading >> lastKnownVelocity >> lastKnownAltitude;
	cout << endl;

	cout << "Using data below the last known point, enter wind data\n"
		<< "(from Bufkit or something) as follows. Finish with CTRL-Z:\n"
		<< "<heading[degrees west of north]> <velocity[m/s]> <altitude[m above ground]>" << endl;

	//pushback vectors with initial position
	latitude.push_back(lastKnownLatitude);
	longitude.push_back(lastKnownLongitude);

	//pushback initial values for said information
	heading.push_back(lastKnownHeading);
	velocity.push_back(lastKnownVelocity);
	altitude.push_back(lastKnownAltitude);

	while (cin >> tempHeading)
	{
		cin >> tempVelocity >> tempAltitude;

		heading.push_back(tempHeading);
		velocity.push_back(tempVelocity);
		altitude.push_back(tempAltitude);
	}
	cout << endl;

	return terminalVelocity;
}


double GetFileData(vector<double> &latitude, vector<double> &longitude, vector<double> &altitude, vector<double> &velocity, vector<double> &heading, char source[])
{
	double lastKnownLatitude;
	double lastKnownLongitude;
	double terminalVelocity;
	double lastKnownHeading;
	double lastKnownVelocity;
	double lastKnownAltitude;
	double tempHeading;
	double tempVelocity;
	double tempAltitude;

	ifstream fin(source);

	fin >> lastKnownLatitude >> lastKnownLongitude >> terminalVelocity;

	fin >> lastKnownHeading >> lastKnownVelocity >> lastKnownAltitude;

	//pushback vectors with initial position
	latitude.push_back(lastKnownLatitude);
	longitude.push_back(lastKnownLongitude);

	//pushback initial values for said information
	heading.push_back(lastKnownHeading);
	velocity.push_back(lastKnownVelocity);
	altitude.push_back(lastKnownAltitude);

	while (fin >> tempHeading)
	{
		fin >> tempVelocity >> tempAltitude;

		heading.push_back(tempHeading);
		velocity.push_back(tempVelocity);
		altitude.push_back(tempAltitude);
	}

	return terminalVelocity;
}


void Extrapolate(vector<double> &latitude, vector<double> &longitude, vector<double> &altitude, vector<double> &velocity, vector<double> &heading, double terminalVelocity)
{
	//cout << "----------\nPath:" << endl;
	for (unsigned int i = 0; i < altitude.size() - 1; ++i)
	{
		double deltaTime;
		double deltaX;
		double deltaY;

		deltaTime = fabs((altitude[i + 1] - altitude[i]) / terminalVelocity);
		deltaY = deltaTime * velocity[i] * cos(GetRad(heading[i]));//delta x in meters (change in longitude)
		deltaX = deltaTime * velocity[i] * sin(GetRad(heading[i]));//delta y in meters (change in latitude)
		//pass in latitude for calculation (because it matters on Earth's surface)
		//add to current coordinates
		latitude.push_back(GetDeltaLat(deltaY, latitude[i]) + latitude[i]);
		longitude.push_back(GetDeltaLon(deltaX, latitude[i]) + longitude[i]);

		//cout << latitude[i] << " " << longitude[i] << " " << altitude[i] << endl;
	}

	//cout << "\n----------\n" << endl;
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


void ExportData(vector<double> &latitude, vector<double> &longitude, vector<double> &altitude)
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