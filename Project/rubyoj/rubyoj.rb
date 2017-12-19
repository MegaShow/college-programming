#========================================================
#  preprocess for Ruby OJ , made by Mega Show
#========================================================

#$KCODE = 'u'
FREPROCESS = "freopen(\"input.txt\",\"r\",stdin);freopen(\"output.txt\",\"w\",stdout);"

def preprocess
	fin = File.new("main.c", "r+")
	if fin
		arr = fin.readlines
	else
		puts "main.c open failed.\n"
		return
	end
	fin.close
	n = 0
	for i in 0...arr.length
		this_line = false
		unless n
			n = arr[i].index("main")
			this_line = true
		end
		if n and this_line
			address = arr[i].index("{", n)
		elsif n
			address = arr[i].index("{")
		end
		if address
			arr[i].insert(address + 1, FREPROCESS)
			break
		end
	end
	fout = File.new("temp_main.c", "w+")
	for i in 0...arr.length
		fout.write(arr[i])
	end
	fout.close
end

def compiler
	system 'gcc temp_main.c'
	system './a.out > output.txt < input.txt'
end

def online_judge
	# your output
	fin = File.new("output.txt", "r+")
	if fin
		arr = fin.readlines
	else
		puts "Judge failed.\n"
		return
	end
	fin.close
	# standard output
	fin = File.new("std_output.txt", "r+")
	if fin
		arr_std = fin.readlines
	else
		puts "Judge failed.\n"
		return
	end
	fin.close
	# compare output
	if arr_std.length != arr.length
		return false
	end
	for i in 0...arr_std.length
		if arr_std[i] != arr[i]
			return false
		end
	end
	return true
end

preprocess

compiler

if online_judge
	puts "Accept!\n"
else
	puts "Wrong Answer!\n"
end

system 'rm a.out'
system 'rm output.txt'
system 'rm temp_main.c'
