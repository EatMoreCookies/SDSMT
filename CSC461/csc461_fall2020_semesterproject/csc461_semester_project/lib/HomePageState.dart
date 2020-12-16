/*
* @author Nathaniel Fagrey
*
*/
import 'package:csc461_semester_project/DisplayStatsPage.dart';
import 'package:flutter/material.dart';
import 'HomePage.dart';
import 'Counter.dart';
import 'Stats.dart';

class HomePageState extends State<HomePage> {
  var myCounter = new Counter();
  var stats = new Stats();
  bool alreadyWarned = false;

  void _incrementCounter() {
    setState(() {
      myCounter.incrementCount();
    });
  }

  void _decrementCounter() {
    setState(() {
      myCounter.decrementCount();
    });
  }

  @override
  Widget build(BuildContext context) {
    // This method is rerun every time setState is called, for instance as done
    // by the _incrementCounter method above.
    //
    // The Flutter framework has been optimized to make rerunning build methods
    // fast, so that you can just rebuild anything that needs updating rather
    // than having to individually change instances of widgets.
    return Scaffold(
      appBar: AppBar(
        // Here we take the value from the MyHomePage object that was created by
        // the App.build method, and use it to set our appbar title.
        title: Text(widget.title),
      ),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.center,
        mainAxisSize: MainAxisSize.max,
        children: <Widget>[
          new Text(
              "Max Customers: " + myCounter.getMaxCustomerCount().toString(),
              style: TextStyle(
                  fontSize: 30.0,
                  fontWeight: FontWeight.bold,
                  color: new Color(0xFF26C6DA))),
          new Container(
            padding: new EdgeInsets.only(top: 16.0),
            child: new Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                new Text('\nCurrent #:  \n',
                    style: new TextStyle(
                      fontSize: 40.0,
                      fontFamily: 'Roboto',
                      color: new Color(0xFF26C6DA),
                    )),
                new Text(
                  '${myCounter.getCustomerCount()}',
                  style: new TextStyle(
                      fontSize: 40.0,
                      fontFamily: 'Roboto',
                      color: new Color(0xFF26C6DA)),
                ),
              ],
            ),
          ),
          new Container(
            padding: new EdgeInsets.only(top: 16.0),
            child: new Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: <Widget>[
                ButtonTheme(
                  minWidth: 100.0,
                  height: 100.0,
                  child: RaisedButton(
                    onPressed: () {
                      _decrementCounter();
                      stats.customererExited();
                      if (myCounter.getCustomerCount() <=
                          myCounter.getCustomerCount()) alreadyWarned = false;
                    },
                    child: Icon(Icons.remove),
                  ),
                ),
                Text("            "),
                ButtonTheme(
                  minWidth: 100.0,
                  height: 100.0,
                  child: RaisedButton(
                    onPressed: () {
                      _incrementCounter();
                      stats.customerEntered();
                      if (myCounter.getCustomerCount() >
                              myCounter.getMaxCustomerCount() &&
                          !alreadyWarned) {
                        alreadyWarned = true;
                        return showDialog(
                          context: context,
                          builder: (context) {
                            return AlertDialog(
                                // Retrieve the text the user has entered by using the
                                // TextEditingController.
                                content: Text("Too many customers!"));
                          },
                        );
                      }
                    },
                    child: Icon(Icons.add),
                  ),
                ),
              ],
            ),
          ),
          SizedBox(height: 50),
          ButtonTheme(
            minWidth: 100.0,
            height: 50.0,
            child: RaisedButton(
              onPressed: () {
                Navigator.push(
                    context,
                    MaterialPageRoute(
                        builder: (context) => DisplayStatsPage(stats)));
              },
              child: const Text('Done'),
            ),
          ),
        ],
      ),
    );
  }
}
