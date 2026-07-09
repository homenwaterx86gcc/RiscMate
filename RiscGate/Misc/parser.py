with open("include_files.txt","r") as file:
    data = file.readlines()
    first_line = data[0]
    data_list = first_line.split(", ")
    data_list = list(reversed(data_list))
    print(data_list)

    with open("sv_headers.txt","w") as file2:
        for f in data_list:
            file2.write(f)
            file2.write("\n")