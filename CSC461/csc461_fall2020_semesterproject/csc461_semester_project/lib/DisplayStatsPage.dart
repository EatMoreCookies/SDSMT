/*
* Jessica Roberts
*/
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'Stats.dart';

class DisplayStatsPage extends StatelessWidget {
  Stats mystats;

  DisplayStatsPage(Stats stats) {
    mystats = stats;
  }

  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("Statistics"),
      ),
      body: Column(
        crossAxisAlignment: CrossAxisAlignment.center,
        mainAxisSize: MainAxisSize.max,
        children: <Widget>[
          SizedBox(height: 20),
          new Text(
              "Total customers that entered: " +
                  mystats.getCustomersEntered().toString(),
              style: TextStyle(
                  fontSize: 20.0,
                  fontWeight: FontWeight.bold,
                  color: new Color(0xFF26C6DA))),
          SizedBox(height: 10),
          new Text(
              "Total customers that exited: " +
                  mystats.getCustomersExited().toString(),
              style: TextStyle(
                  fontSize: 20.0,
                  fontWeight: FontWeight.bold,
                  color: new Color(0xFF26C6DA))),
        ],
      ),
    );
  }
}
