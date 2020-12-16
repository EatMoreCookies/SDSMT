package fagrey_nathaniel;

import java.util.InputMismatchException;
import java.util.Scanner;

public class SolarStart {

    public static Scanner cin; //intentionally public for ease of use

    public static void main(String[] args) {
        cin = new Scanner(System.in);
        String menu =
                "\n1) Set Area\n" +
                        "2) Remove Area\n" +
                        "3) Make Default Grid\n" +
                        "4) Count Types\n" +
                        "5) Set Type Color\n" +
                        "6) Light Up Bulbs\n" +
                        "0) Quit\n";
        int input = -1;

        Grid grid = new Grid();
        System.out.print( "\n");

        while (input != 0) {
            System.out.print( "\n");
            grid.printGrid();
            System.out.print(menu);
            System.out.println();
            System.out.print("Choice: ");

            try {
                input = cin.nextInt();

                if( input < 0 || input > 6 ){
                    System.out.println( "Unknown Option");
                }

                else if( input == 0 ){
                    return;
                }

                else {
                    switch(input){
                        case 0:
                            break;
                        case 1:
                            grid.setArea(cin);
                            break;
                        case 2:
                            grid.removeArea(cin);
                            break;
                        case 3:
                            grid.makeDefaultGrid();
                            break;
                        case 4:
                            grid.countTypes();
                            break;
                        case 5:
                            grid.colorType(cin);
                            break;
                        case 6:
                            grid.colorLightBulb();
                            break;
                    }
                }
            } catch (InputMismatchException e) {
                System.out.println("Invalid Option");
                cin.nextLine();
            }

            catch( Exception e ){
                System.out.println("Invalid Option");
                cin.nextLine();
            }
        }
    }
}

