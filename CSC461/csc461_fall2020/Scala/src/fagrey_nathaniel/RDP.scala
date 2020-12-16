package fagrey_nathaniel
import scala.xml._

trait RDP{
  def xmlRead(node : Node) : Unit
  def xmlWrite() : Elem
  def add() : Unit
  def displayString( starter: String) : String
}
