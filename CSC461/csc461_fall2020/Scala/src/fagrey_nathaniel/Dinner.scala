package fagrey_nathaniel
import scala.io.Source
import scala.collection.mutable.ListBuffer
import scala.xml
import scala.xml._
import java.io.FileNotFoundException

class Dinner() extends RDP with CoR{

  private var houses = new ListBuffer[House]()

  // GRADING: ADD
  def add(): Unit = {

    print("What house code: ")
    val input = io.StdIn.readInt()
    var houseExits = false

    if (houses.nonEmpty) {
      for (house <- houses) {
        if (house.getId == input) {
          houseExits = true
          house.add()
        }
      }
    }

    if (!houseExits) {
      houses += House(input)
      print("Added house code")
    }
  }

  // GRADING: PRINT
  override def displayString(starter: String): String = {
    var returnString = starter
    for (house <- houses) {
      returnString += "\n" + house.displayString("")
    }
    returnString
  }

  def remove() : Unit = {
    print("What house code: ")
    val input = io.StdIn.readInt()
    var index = 0
    var houseFound = false

    for( house <- houses){
      if( house.getId == input) {
        houses.remove(index)
        houseFound = true
      }

      index += 1
    }

    if(houseFound)
      print( s"Removed $input")

    else
      print("House code not Found")

  }

  override def xmlRead(node: Node): Unit = {
    print("File Name: ")
    val fileName = io.StdIn.readLine()

    try {
      val topNode = XML.loadFile(fileName) //XML.loadFile will read in the DOM tree

      if (topNode.label != "dinner") { //.label is the "tag"
        println("Invalid XML file. Needs to be an dinner XML file")
      }

      else {
        // GRADING: READ
        val children = topNode.child
        for (child <- children) {
          val tag = child.label
          tag match {
            case "house" =>
              val code = child.attribute("code").getOrElse("").toString
              val tempId = child.attribute("id").getOrElse("").toString
              var house: House = null

              if (code != "")
                house = House(code.toInt)

              else if (tempId != "")
                house = House(tempId.toInt)
              house.xmlRead(child)
              houses += house
            case _ => null
          }
        }
      }
    }

    catch {
      case e: FileNotFoundException => println("Could not open file: " +  e.getMessage)

    }
  }

  def xmlWrite(): Elem = {
    // GRADING: WRITE
    val houseXml = houses.map(x => x.xmlWrite())
    XMLHelper.makeNode("dinner", null, houseXml)

  }

  def findFood(foodName: String): Boolean = {
    for(house <- houses){
      if( house.findFood(foodName))
        return true
    }

    false
  }

  def leftOvers(): Unit = {
    print("What house code: ")
    val houseCode = io.StdIn.readInt()
    var leftOvers = 0.0

    // GRADING: LEFTOVERS
    val house = houses.par.find( house => house.getId == houseCode)
    leftOvers = house.get.calculateLeftOvers()

    print(s"Total Leftovers: $leftOvers lbs")
  }

}

object Dinner {
  def apply () : Dinner = new Dinner()
}