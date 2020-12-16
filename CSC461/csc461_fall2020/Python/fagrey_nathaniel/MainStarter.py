from fagrey_nathaniel.Line import Line

def main():
    menu = "\n" \
           "1) Show Train Line\n" \
           "2) Add Train Car\n" \
           "3) Update with Debug Info\n" \
           "4) Show Station Details\n" \
           "5) Make Test Line \n" \
           "6) Make Custom Line \n" \
           "0) Quit\n"


    choice = -1
    line = Line()


    while choice != 0:
        print(menu)
        choice = input("Choice: ")

        # strips out blank lines in input
        while choice == '':
            choice = input( )

        if choice == '1':
            line.print_line()

        elif choice == '2':
            line.add_car()

        elif choice == '3':
            line.update()

        elif choice == '4':
            line.show_stations()

        elif choice == '5':
            line.make_test_line()

        elif choice == '6':
            line.add_station()

        elif choice == '0':
            choice = 0
        else:
            print("Invalid Option")


if __name__ == '__main__':
    main()