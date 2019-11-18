# CameraViewer
Python version works with anaconda opencv3
 ELP-USBFHd04H-L170 camera viewer 
 
 for Visual studio version:
 - Visual Studio 2019 free version
 - vcpkg which is found here: https://github.com/Microsoft/vcpkg
  help here: https://github.com/microsoft/vcpkg/blob/master/docs/examples/installing-and-using-packages.md
 - follow the install instructions which basically is to download and run:  .\bootstrap-vcpkg.bat using powershell
 - install opencv4 (4.1.2) 32bits and 64bits just in case someone needs 32bits.
	   from power shell:
	   for 32 bits:
		  .\vcpkg.exe install opencv4
	   for 64 bits: 
		  .\vcpkg.exe install opencv4:x64-windows
 - incorporate the packages into visual studio:
    .\vcpkg.exe integrate install


Instructions for use:
              case 'q':
                      goto out;
              case 'Q':
                      goto out;

              // canny parameters:
              case '1':
                      cannythreashold1 += 5;
                      break;
              case '!':
                      cannythreashold1 -= 5;
                      break;
              case '2':
                      cannythreashold2 += 5;
                      break;
              case '@':
                      cannythreashold2 -= 5;
                      break;
              case '3':
                      l2gradient != l2gradient;
                      break;
              case '4': // restore default values
                      l2gradient = false;
                      cannythreashold1 = 30;
                      cannythreashold2 = 60;
                      alpha = 1;
                      beta = 0;
                      break;

              // brightness and contrast parameters
              //     Enter the alpha value[1.0 - 3.0]: 2.2
              //   Enter the beta value[0 - 100] : 50
              case 'b': 
                      if (beta == 100) break;
                      beta += 1;
                      break;
              case 'B': 
                      if (beta == 0) break;
                      beta -= 1;
                      break;
              case 'c': 
                      if (alpha == 3) break;
                      alpha += 0.1;
                      break;
              case 'C': 
                      if (alpha == 1) break;
                      alpha -= 0.1;
                      break;

