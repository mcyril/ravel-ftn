"""imgconvert - A very simple image converter."""import imgimport sysimport os# Set trace, so we can see what happensimg.settrace(1)if os.name == 'mac':	import macfs	fss, ok = macfs.StandardGetFile()	if not ok: sys.exit(0)	infile = fss.as_pathname()	fss, ok = macfs.StandardPutFile('Output?')	if not ok: sys.exit(0)	outfile = fss.as_pathname()else:	if len(sys.argv) <> 3:	    print 'Usage:',sys.argv[0],'inimage outimage'	    sys.exit(1)	infile = sys.argv[1]	outfile = sys.argv[2]## Create a non-converting writer (we do conversion in the reader)#writer = img.writer(None, outfile)## Create a reader that converts to the preferred output format#reader = img.reader(writer.format, infile)## Set output file parameters#writer.width, writer.height = reader.width, reader.heightif reader.format.descr['type'] == 'mapped':    writer.colormap = reader.colormap## Copy the data#writer.quality = 30writer.restart_interval=1data = reader.read()writer.write(data)## Done#sys.exit(0)