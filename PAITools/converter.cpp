#include "converter.h"

BOOL CONVERTER_FUNCTION(std::string INFILE_ARG, std::string OUTPUTFILE_ARG, int QUAL_ARG, std::string DPI_ARG)
{
	try {
		Magick::InitializeMagick(".");
		Magick::Image MYIMAGE;
		MYIMAGE.quality(QUAL_ARG);
		MYIMAGE.resolutionUnits(Magick::PixelsPerInchResolution);
		MYIMAGE.density(DPI_ARG);
		MYIMAGE.read(INFILE_ARG);
		MYIMAGE.write(OUTPUTFILE_ARG);
	}
	catch (Magick::Exception &error_)
	{
		std::cout << "Caught exception: " << error_.what() << std::endl;
		return FALSE;
	}
	return TRUE;
}
