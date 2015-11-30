"""A minimal module to write Mac 24-bit RGB PICT files on any machine"""## Macintosh PICT format reader/writer module## Jack Jansen, CWI, 1995#import structimport imgformatimport imgoperror = imgformat.errorclass reader:    def __init__(self, filename):	self._filename = filename	self.width = 0	self.height = 0	raise error, 'Reading PICT files not yet supported'    def args(self):	return self.__dict__	    def read(self):	return ''    def write(self, data):	raise error, 'Cannot write() to reader'class writer:    """This object can write to a pict file. The width, height and format    attributes should be set before calling write()"""        def __init__(self, file):    	if type(file) == type(''):		self._filename = file		self._fp = None	else:		self._fp = file		self._filename = "<open file>"	self.format_choices = (imgformat.macrgb, )	self.format = imgformat.macrgb    def args(self):	return self.__dict__	    def _get(self, attr):	try:	    return getattr(self, attr)	except AttributeError:	    raise error, "Required attribute '%s' missing"%attr    def read(self):	raise error, 'Cannot read() from writer'    def write(self, data):	"write the actual data"		w = self._get('width')	h = self._get('height')	fmt = self._get('format')	if fmt <> imgformat.macrgb:		raise error, 'Only macrgb currently supported'	if w*h*4 != len(data):	    raise error, 'Incorrect datasize'	# Create the image structure. This is tricky due to possible alignment	imgstruct = struct.pack('hhhhh', 0x011, 0x02ff, 0x0c00, -2, 0)[:10]	imgstruct = imgstruct + struct.pack('llhhhh', 0x480000, 0x480000, 0, 0, h, w)	imgstruct = imgstruct + struct.pack('l', 0)	imgstruct = imgstruct + struct.pack('h', 0x9a)[:2]	imgstruct = imgstruct + struct.pack('l', 0xff)	imgstruct = imgstruct + struct.pack('hhhhhhh', 0x8000|(w*4),			0, 0, h, w, 0, 1)[:14]	imgstruct = imgstruct + struct.pack('lll', 0, 0x480000, 0x480000)	imgstruct = imgstruct + struct.pack('hhhh', 16, 32, 3, 8)##	imgstruct = imgstruct + struct.pack('lll', 0, 0, 0)##	imgstruct = imgstruct + struct.pack('l', 0x1000000)##	imgstruct = imgstruct + struct.pack('hh', 0, 0)##	imgstruct = imgstruct + struct.pack('hhhh', -1, 0, 0, 0)	imgstruct = imgstruct + struct.pack('lll', 0, 0xad892c, 0)  # ????	imgstruct = imgstruct + struct.pack('hhhh', 0, 0, h, w)	imgstruct = imgstruct + struct.pack('hhhh', 0, 0, h, w)	imgstruct = imgstruct + struct.pack('h', 0)[:2]		length = len(imgstruct) + len(data) + 10 + 2	imghdr = struct.pack('hhhhh', length&0xffff, 0, 0, h, w)[:10]	imgtrailer = struct.pack('h', 0xff)[:2]		if self._fp:		fp = self._fp	else:		fp = open(self._filename, 'wb')	fp.write('\0'*512)	fp.write(imghdr)	fp.write(imgstruct)	fp.write(data)	fp.write(imgtrailer)	fp.close()		try:		import macfs		macfs.FSSpec(self._filename).SetCreatorType('????', 'PICT')	except ImportError:		# We're probably not running on a mac		pass		def _test():	import imgppm		r = imgppm.reader('in-rgb-t2b.ppm')	w = writer('out-mac.pict')	w.width, w.height = r.width, r.height	d = r.read()	d = imgop.shuffle(d, r.width, r.height, r.format, w.format)	w.write(d)if __name__ == '__main__':	_test()	