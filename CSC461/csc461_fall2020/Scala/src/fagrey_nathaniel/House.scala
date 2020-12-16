package fagrey_nathaniel
import scala.collection.mutable
import scala.collection.mutable.ListBuffer
import scala.xml._

class House( private var id: Int ) extends RDP with CoR{
  private var persons = new ListBuffer[Person]()


  override def add( ) : Unit = {
    print("\nWhat person: ")
    val input = io.StdIn.readLine()
    var personExits = false

    if (persons.nonEmpty) {
      for (person <- persons) {
        if (person.getName.toLowerCase() == input.toLowerCase() ) {
          personExits = true
          person.add()
        }
      }
    }

    if (!personExits) {
      persons += Person(input)
      print("Added person")
    }
  }

  def getId: Int= {
      return id
  }

  override def displayString(starter: String): String = {
    var returnString = starter + "House: " + id.toString

    for (person <- persons) {
      returnString += person.displayString(starter + "--")
    }
    returnString
  }

  override def xmlWrite(): Elem = {
    val attr: mutable.HashMap[String, String] = mutable.HashMap(("code", id.toString))

    val personXml = persons.map(x => x.xmlWrite())
    XMLHelper.makeNode("house", attr, personXml)
  }

  override def xmlRead(node : Node): Unit = {
    val children = node.child
    for (child <- children) {
      val tag = child.label
      tag match {
        case "person" =>
          val tempName = child.attribute("name").getOrElse("").toString
          val person = Person(tempName)
          person.xmlRead(child)
          persons += person
        case _ => null
      }
    }
  }

  def findFood(foodName: String): Boolean = {
    // GRADING: FIND
    for( person <- persons){
      if( person.findFood(foodName))
        return true
    }

    false
  }

  def calculateLeftOvers(): Double = {
    var totalFood = 0.0
    var totalNeed = 0

    for( person <- persons){
      totalNeed += person.getFoodRequired
      totalFood += person.getTotalFood
    }

    totalFood - totalNeed
  }

}

object House {
  def apply(id: Int): House = new House(id)
}
