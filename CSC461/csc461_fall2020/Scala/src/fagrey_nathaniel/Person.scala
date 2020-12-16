package fagrey_nathaniel
import scala.collection.mutable
import scala.collection.mutable.ListBuffer
import scala.xml._

class Person(private var name: String) extends RDP with CoR{
  private var foods = new ListBuffer[Food]()
  private var hunger = 1
  private var stay = Stay()

  def add(): Unit = {
    print("\nAdd hunger: ")
    hunger = io.StdIn.readInt()

    addStay()

    addFood()
  }

  private def addStay(): Unit = {
    print("\nAdd stay y/n?")
    val stayOption = io.StdIn.readChar()

    if (stayOption.toLower == 'y'){
      stay.add()
    }
  }

  private def addFood() : Unit = {
    var option = 'y'

    do
    {
      print( "\nAdd food y/n? ")
      option = io.StdIn.readChar()

      if( option.toLower == 'y'){
        val newFood = Food()
        newFood.add()
        foods += newFood
      }

      } while( option.toLower != 'n')
  }

  override def displayString(starter: String): String = {
    var returnString = f"\n${starter}Name: $name%-10s Hunger: $hunger\n${starter}--Stay:"
    returnString += stay.displayString(starter + "--")

    if( foods.nonEmpty ) {
      returnString += s"\n${starter}--Food:"
      for (food <- foods) {
        returnString += food.displayString(starter + "--")
      }
    }
    returnString
  }

  def getName: String = name

  def addHunger(hunger: Int): Unit = {
    this.hunger = hunger
  }

  override def findFood(foodName: String): Boolean = {
      for( food <- foods ){
        // GRADING: CHAIN
        if( food.findFood(foodName)) {
          print(s"$name brought ${food.getFood} (${food.getWeight} lbs).")
          return true
        }
      }
    false
  }

  override def xmlWrite(): Elem = {
    val attr: mutable.HashMap[String, String] = mutable.HashMap(("name", name))
    attr("hunger") = hunger.toString


    var stays = new ListBuffer[Stay]()
    stays += stay

    val stayXml = stays.map(x => x.xmlWrite())

    val foodXml = foods.map(x => x.xmlWrite())

    val combined = stayXml ++ foodXml

    XMLHelper.makeNode("person", attr, combined)
  }

  override def xmlRead(node : Node): Unit = {
    hunger = node.attribute("hunger").getOrElse("1").toString.toInt
    val children = node.child
    for (child <- children) {
      val tag = child.label
      tag match {
        case "stay" =>
          stay.xmlRead(child)
        case "food" =>
          val food = Food()
          food.xmlRead(child)
          foods += food
        case _ => null
      }
    }
  }

  def getFoodRequired: Int = {
    stay.getDays * hunger
  }

  def getTotalFood: Double = {
    var sum: Double = 0

    for( food <- foods )
      sum += food.getWeight
    sum
  }
}

object Person {
  def apply(name: String): Person = new Person(name)
}
