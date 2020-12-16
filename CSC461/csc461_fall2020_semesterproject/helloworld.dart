// Importing Packages

// Needed for file in/out
import 'dart:io';

//Needed for utfdecoding and linsplitter
import 'dart:convert';

/*
* writes terminal inputs to a file
*/
void writeFile(file){
    // Open File
    var myFile = new File(file);

    print("Enter Text (end with 'end'): ");
    List msg = [];
    String m = "";

    // While loop
    while ((m = stdin.readLineSync()).toLowerCase() != "end"){
        // Append an item to a list
        msg.add(m+"\n");
    }

    // You can join a list of strings into one string with a seperation
    m = msg.join();

    // Write to file
    myFile.writeAsStringSync(m);

}

double changeMe(num){
    num = 5.0;
    return num;
}

/*
*  prints the contents of a file to the terminal
*
*  Allows for asyncronous operations to occur
*  async is needed to use the await keyword which allows
*  the for each loop to go through a Stream<String>
*  but async is not needed if await is not used
*/
void readFile(file) async{
    // lines is a Stream<String>
    final lines = utf8.decoder
          .bind(File(file).openRead())
          .transform(const LineSplitter());

    await for (var line in lines) {
        // This is another way of printing to terminal
      stdout.writeln(line);
    }
}



class Parent {
    void func1(String a){ print("value of a ${a} first");}
}
class Child extends Parent {
    @override
    void func1(String a) {
        print("value of a ${a} second");
    }

}

Function makeAdder(int addBy) {
    return (int i) => addBy + i;
}

void main() {

    double type1 = 1.0;
    var type2 = 1.0;
    print("double type1 = 1.0; is ${type1.runtimeType}\nvar type2 = 1.0; is ${type2.runtimeType}");

    print("Before call $type1");
    var tmp = changeMe(type1);
    print("Returned $tmp, and after call $type1");


    // Create a function that adds 2.
    var add2 = makeAdder(2);

    // Create a function that adds 4.
    var add4 = makeAdder(4);

    assert(add2(3) == 5);
    assert(add4(3) == 7);




    // Print to screen
    print("Enter your name?");

    // Read from CLI, notice the 'var' there is type inference
    var name = stdin.readLineSync();


    // Typical if statement
    // Nice format strings
    if (name == "Dart"){
        print("Hey we're in a conditional because you entered $name");
    }else{
        print("Hello $name");
    }

    print("What File do you want to write?");

    String file = stdin.readLineSync();

    print("Your File is $file");

    // Function Call
    writeFile(file);

    print("Enter Two (2) numbers to add together: ");

    try{
        print("Number 1: ");
        double one = double.parse(stdin.readLineSync());
        print("Number 2: ");
        double two = double.parse(stdin.readLineSync());
        double three = one + two;
        print("$one + $two = $three");

    }catch (e){
        print("Something went wrong");
            print(e);
    }

    // This doesnt add a newline at the end
    stdout.write("Do you want to read that file? (y/n): ");

    String read = stdin.readLineSync();

    // Useful string functions like toLowerCase exist
    if (read.toLowerCase() == "y"){
        readFile(file);
    }



}
