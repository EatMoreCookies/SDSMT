/*
* Jessica Roberts
*/
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'Counter.dart';
import 'HomePage.dart';

class CustomerInput extends StatelessWidget {
  final customerCountController = TextEditingController();

  void dispose() {
    customerCountController.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        body: new Container(
      padding: const EdgeInsets.all(40.0),
      child: new Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: <Widget>[
          TextField(
            controller: customerCountController,
            decoration:
                new InputDecoration(labelText: "Enter max customers allowed"),
            keyboardType: TextInputType.number,
            inputFormatters: <TextInputFormatter>[
              FilteringTextInputFormatter.digitsOnly
            ], // Only numbers can be entered
          ),
          const SizedBox(height: 30),
          RaisedButton(
            onPressed: () {
              var myCounter = Counter();
              myCounter
                  .setMaxCustomerCount(int.parse(customerCountController.text));
              Navigator.push(
                  context,
                  MaterialPageRoute(
                      builder: (context) =>
                          HomePage(title: "Count Customers")));
            },
            child:
                const Text('Start Counting!', style: TextStyle(fontSize: 20)),
          ),
          SizedBox(height: 10),
          RaisedButton(
            onPressed: () {
              var myCounter = new Counter();
              myCounter.clear();

              return showDialog(
                context: context,
                builder: (context) {
                  return AlertDialog(content: Text("Cleared Count"));
                },
              );
            },
            child: const Text('Clear Counting', style: TextStyle(fontSize: 20)),
          ),
        ],
      ),
    ));
  }
}
