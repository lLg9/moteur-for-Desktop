'''
_g9
moteur appender script for moteur_english
2019.01.01. 

Features: 
	adds words and updates ranks also
	week & start_pos have to be specified
	must be launched from the dir where the updatable db files are located
	addable words shall be stored in a #add.fgnt file (format: <word>; <translation><newline>)

! if __name__ protected 
'''

def main(): 

	#data_append
	week = 37
	start_pos = 20

	#----------------------------------------------

	entry_no = start_pos
	counter = 0 

	datalines = []

	with open('#add.fgnt', 'r') as inputfile: 
		line_no = 0
		for line in inputfile: 
			line_no += 1
			if line.count(";") != 2:
				print("ERROR_;;;_NO", line_no)
				return
			datalines.append(line)

	with open('#data.fgnt', 'a+') as datafile:
		for line in datalines: 
			entry = str(entry_no) + ' ; ' + str(week) + ' ; ' + "[0, 0, 0, 0, 0, 0, 0, 0, 0, 0]" + ' ; ' + line
			datafile.write(entry)
			entry_no += 1 
			counter += 1 
		datafile.write('\n')

	#-----------------------------------------------
	
	#rank_append
	good = []
	medium = []
	poor = []
	
	if (start_pos > 0):
		with open('#ranks.fgnt', 'r') as inp: 
			good = inp.readline().strip().split()
			medium = inp.readline().strip().split()
			poor = inp.readline().strip().split()
			print(poor)

	for i in range(start_pos, start_pos+counter):
		poor.append(str(i))

	print(poor)

	with open('#ranks.fgnt', 'w') as ouf:
		for n in good: 
			ouf.write(n)
			ouf.write(' ')
		ouf.write('\n')

		for n in medium: 
			ouf.write(n)
			ouf.write(' ')
		ouf.write('\n')

		for n in poor: 
			ouf.write(n)
			ouf.write(' ')
		ouf.write('\n')





		


if __name__ == '__main__':
	pass
	# main()