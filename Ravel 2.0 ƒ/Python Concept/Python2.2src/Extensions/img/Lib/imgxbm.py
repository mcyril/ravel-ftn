## XBM image reader/writer module, python version#import stringimport imgformaterror = imgformat.errorclass reader:	"Object that reads the image."		def __init__(self, file):		"""Initialize. You should read the header and fill in attributes		such as width, height, format_choices, format and colormap"""				if type(file) == type(''):			self._filename = filename			self._fp = open(filename, 'rb')  # Yes, rb. Let's assume unix eolns...		else:			self._filename = '<open file>'			self._fp = file		self.width = self._getdefine()		self.height = self._getdefine()		self.format = imgformat.xbmpacked		self.format_choices = (self.format,)			def _getdefine(self):		while 1:			line = self._fp.readline()			if not line:				raise error, 'No #define found, not an XBM file?'			while line[-1] in ('\r', '\n'): line = line[:-1]			line = string.split(line)			if len(line) == 3 and line[0] == '#define':				return string.atoi(line[2])	def args(self):		return self.__dict__			def read(self):		"Read the image data"		data = self._fp.read()		try:			bropen = string.index(data, '{')			brclose = string.index(data, '}')		except ValueError:			raise error, 'No braces found, not an XBM file?'		data = '(' + data[bropen+1:brclose-1] + ')'		try:			data = eval(data)		except ValueError:			raise error, 'Hexadecimal data not parseable, not an XBM file?'		rv = ''		for d in data:			# Note that xbm have white=0, black=1			rv = rv + chr(255-d)		return rv	def write(self, data):		raise error, 'Cannot write() to reader'class writer:	"Object that writes to an image file"		def __init__(self, file):		if type(file) == type(''):			self._filename = filename			self._fp = None		else:			self._filename = '<open file>'			self._fp = file		self._filename = filename	def args(self):		return self.__dict__			def _get(self, attr):		try:			return getattr(self, attr)		except AttributeError:			raise error, "Required attribute '%s' missing"%attr	def read(self):		raise error, 'Cannot read() from writer'	def write(self, data):		"""Write the image file, according to attribute format"""				w = self._get('width')		h = self._get('height')		if w*h != len(data):			raise error, 'Incorrect datasize'			