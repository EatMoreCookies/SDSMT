package fagrey_nathaniel;

import javafx.geometry.Pos;
import javafx.event.ActionEvent;
import javafx.scene.control.*;
import javafx.scene.layout.*;

public class Layout{

    public ApartmentComplex apartmentComplex;
    public ApartmentComplexView apartmentComplexView;
    public Controller controller;
    public InfoBar infoBar;

    public Label rentToCollect = new Label();
    public Label maintenence = new Label();
    public Label filled = new Label();
    public Label month = new Label();
    public Label funds = new Label();


    Layout(){
        apartmentComplex = new ApartmentComplex();
        apartmentComplexView = new ApartmentComplexView();
        controller = new Controller(apartmentComplex, apartmentComplexView);
        apartmentComplexView.setModel(apartmentComplex, controller);
        infoBar = new InfoBar(apartmentComplex, maintenence, filled, funds, rentToCollect, month);
    }

    public HBox makeLayout() {
        HBox root = new HBox();

        VBox inforBarR = new VBox();
        VBox inforBarL = new VBox();

        Region spacer1 = new Region();
        VBox.setVgrow(spacer1, Priority.ALWAYS);

        inforBarL.getChildren().addAll(rentToCollect, maintenence, filled, spacer1, month, funds );
        inforBarL.setSpacing(5);

        Button newMonth = new Button("New Month");
        newMonth.addEventFilter(ActionEvent.ACTION, controller.new newMonthEvent());

        TextField rentIncreaseTextBox = new TextField();

        Button increaseRent = new Button("Increase Rent");
        increaseRent.addEventFilter(ActionEvent.ACTION, controller.new increaseRentEvent(rentIncreaseTextBox));

        rentIncreaseTextBox.setMaxWidth(100);

        ToggleGroup tg = new ToggleGroup();
        RadioButton empty = new RadioButton("Empty");
        empty.setSelected(true);
        empty.setToggleGroup(tg);

        RadioButton basic = new RadioButton("Basic");
        basic.setToggleGroup(tg);

        RadioButton penthouse = new RadioButton("Penthouse");
        penthouse.setToggleGroup(tg);

        MenuBar menuBar = new MenuBar();
        Menu menu = new Menu("# Buildings");

        MenuItem build3 = new MenuItem("3 Buildings");
        build3.setOnAction(controller.new BuildComplex(3));
        menu.getItems().add(build3);

        MenuItem build4 = new MenuItem("4 buildings");
        build4.setOnAction(controller.new BuildComplex(4));
        menu.getItems().add(build4);

        MenuItem build6 = new MenuItem("6 buildings");
        build6.setOnAction(controller.new BuildComplex(6));
        menu.getItems().add(build6);

        menuBar.getMenus().add(menu);
        menuBar.setMaxWidth(100);

        Region spacer2 = new Region();
        Region spacer3 = new Region();
        Region spacer4 = new Region();
        Region spacer5 = new Region();

        VBox.setVgrow(spacer2, Priority.ALWAYS);
        VBox.setVgrow(spacer3, Priority.ALWAYS);
        VBox.setVgrow(spacer4, Priority.ALWAYS);
        VBox.setVgrow(spacer5, Priority.ALWAYS);

        inforBarR.getChildren().addAll(newMonth, spacer2, rentIncreaseTextBox, increaseRent,
                spacer3, empty, basic, penthouse, spacer4, menuBar, spacer5);
        inforBarR.setSpacing(5);
        inforBarR.setAlignment(Pos.CENTER);


        Region spacer6 = new Region();
        Region spacer7 = new Region();
        HBox.setHgrow(spacer6, Priority.ALWAYS);
        HBox.setHgrow(spacer7, Priority.ALWAYS);

        controller.setToggleGroup(tg);
        HBox.setHgrow(apartmentComplexView, Priority.ALWAYS);
        root.setSpacing(10);
        root.getChildren().addAll(inforBarL, apartmentComplexView, inforBarR);

        return root;
    }
}
