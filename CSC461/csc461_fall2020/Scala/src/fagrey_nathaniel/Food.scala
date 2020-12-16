package fagrey_nathaniel

import scala.collection.mutable
import scala.xml._

class Food extends RDP with CoR{
  var name : String = ""
  var weight : Double = 0.00

  override def add(): Unit = {
    print("\nName: ")
    name = io.StdIn.readLine()

    print("Weight: ")
    weight = io.StdIn.readDouble()
  }

  override def displayString(starter: String): String = {
    var returnString = f"\n$starter--Name: $name ($weight%2.1f lbs)"
    returnString
  }

  override def xmlWrite(): Elem = {
    val attr: mutable.HashMap[String, String] = mutable.HashMap(("name", name))
    val text = Text(weight.toString)

    XMLHelper.makeNode("food", attr, text )
  }

  override def xmlRead(node : Node): Unit = {
    name =  node.attribute("name").getOrElse("").toString
    if( node.text != "") weight = node.text.toFloat
  }

  override def findFood(foodName: String): Boolean = {
    if( foodName.toLowerCase == name.toLowerCase )
      return true
    false
  }

  def getFood: String = name

  def getWeight: Double = weight
}

object Food {
  def apply(): Food = new Food()
}