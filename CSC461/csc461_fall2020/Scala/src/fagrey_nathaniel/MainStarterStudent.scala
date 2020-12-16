package fagrey_nathaniel
import java.text.DecimalFormat

import scala.io.StdIn
import scala.xml.XML



object MainStarterStudent extends App {
    var choice = -1

    val menu: String =
        """
          |1) Add data
          |2) Display data
          |3) Remove house
          |4) Load XML
          |5) Write XML
          |6) Find food
          |7) Estimate leftovers
          |0) Quit
          |Choice: """.stripMargin

    var temp = ""
    var dinner = Dinner()
    while (choice != 0) {
        try {
            print(menu)
            //something to strip out empty lines
            temp = StdIn.readLine()
            while(temp.isEmpty)
                temp = StdIn.readLine()
            choice = temp.toInt

            choice match {
                case 0 => choice = 0
                case 1 => dinner.add()
                case 2 => print( dinner.displayString("") )
                case 3 => dinner.remove()
                case 4 => dinner.xmlRead(null)
                case 5 =>
                    print( "File Name: ")
                    val fileName = io.StdIn.readLine()
                    val newDinner = dinner.xmlWrite()
                    XML.save(fileName, newDinner, "UTF-8", true, null)
                case 6 =>
                  print("Food: ")
                  val food = io.StdIn.readLine()
                  if( !dinner.findFood(food))
                    print(food + " not found")

                case 7 => dinner.leftOvers()
                case _ => println("Invalid option")
            }
        } catch {
            case e: Throwable => print(e)
        }
    }
}

