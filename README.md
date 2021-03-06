# atmospheric-data-analysis
This code analyzes data from the National Oceanic and Atmospheric Administration (NOAA) North American Mesoscale Forecast System and outputs information about the climate in a few different states.

To run the program, download the code and navigate to the working directory. Insert the data as a file(s) you wish to parse (downloaded by state from NOAA's website).
When you have added the data to analyze, run the code with the command `./climate state.file`

Say you added files containing information on TN and WA. The following outlines the expected run command and output:

`./climate data_tn.tdv data_wa.tdv`

Example run:
```
 Opening file: data_tn.tdv
 Opening file: data_wa.tdv
 States found: TN WA
 -- State: TN --
 Number of Records: 17097
 Average Humidity: 49.4%
 Average Temperature: 58.3F
 Max Temperature: 110.4F on Mon Aug  3 11:00:00 2015
 Min Temperature: -11.1F on Fri Feb 20 04:00:00 2015
 Lightning Strikes: 781
 Records with Snow Cover: 107
 Average Cloud Cover: 53.0%
 -- State: WA --
 Number of Records: 48357
 Average Humidity: 61.3%
 Average Temperature: 52.9F
 Max Temperature: 125.7F on Sun Jun 28 17:00:00 2015
 Min Temperature: -18.7F on Wed Dec 30 04:00:00 2015
 Lightning Strikes: 1190
 Records with Snow Cover: 1383
 Average Cloud Cover: 54.5%
 ```
 TDV format:
 ```
 CA» 1428300000000»  9prcjqk3yc80»   93.0»   0.0»100.0»  0.0»95644.0»277.58716
 CA» 1430308800000»  9prc9sgwvw80»   4.0»0.0»100.0»  0.0»99226.0»282.63037
 CA» 1428559200000»  9prrremmdqxb»   61.0»   0.0»0.0»0.0»102112.0»   285.07513
 CA» 1428192000000»  9prkzkcdypgz»   57.0»   0.0»100.0»  0.0»101765.0» 285.21332
 CA» 1428170400000»  9prdd41tbzeb»   73.0»   0.0»22.0»   0.0»102074.0» 285.10425
 CA» 1429768800000»  9pr60tz83r2p»   38.0»   0.0»0.0»0.0»101679.0»   283.9342
 CA» 1428127200000»  9prj93myxe80»   98.0»   0.0»100.0»  0.0»102343.0» 285.75
 CA» 1428408000000»  9pr49b49zs7z»   93.0»   0.0»100.0»  0.0»100645.0» 285.82413
 ```
 Each field is separated by a tab character \t and ends with a newline \n.
 
 Fields:
 * state code (e.g., CA, TX, etc),
 * timestamp (time of observation as a UNIX timestamp),
 * geolocation (geohash string),
 * humidity (0 - 100%),
 * snow (1 = snow present, 0 = no snow),
 * cloud cover (0 - 100%),
 * lightning strikes (1 = lightning strike, 0 = no lightning),
 * pressure (Pa),
 * surface temperature (Kelvin)
