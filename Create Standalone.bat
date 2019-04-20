rmdir /S /Q Standalone
mkdir Standalone
cd Standalone
mkdir DigiPengs
xcopy /Y ..\Release\DigitalPenguins.exe DigiPengs
xcopy /Y ..\Release\*.dll DigiPengs
xcopy /I /S /Y ..\Assets DigiPengs\Assets