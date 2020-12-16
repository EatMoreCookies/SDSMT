/*
* @author Ashlyn Davie
*/
import 'package:flutter/material.dart';
import 'CustomerInput.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'CSC461 Semester Project',
      theme: ThemeData(
        primarySwatch: Colors.green,
        visualDensity: VisualDensity.adaptivePlatformDensity,
      ),
      home: CustomerInput(),
    );
  }
}
