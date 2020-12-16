package fagrey_nathaniel;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.file.Paths;
import java.util.Scanner;

/**
 * This class will test your output against the given file list. This class will be OVERWRITTEN on our end.
 */
public class RunTests {

    public static final boolean RUN_TESTS = true;
    public static final boolean CHECK_CAP = false;
    public static final boolean CHECK_LEFT_SPACING = false;
    public static final boolean CHECK_RIGHT_SPACING = false;
    public static final boolean CHECK_NEW_LINE = false;

    public static void main(String[] args)  {

        //no argument try once to get it from the user
        if (RUN_TESTS) {
            try {
                String[] tests = {"tier1", "tier2", "tier3","tier4", "tier5", "tier6", "tier7", "tier8", "tier9"};

                for (String base : tests) {
                    String inFile = base + ".txt";
                    String runOutFile = base + "-student.out";
                    String answerFile = base + ".out";
                    boolean error = false;

                    //redirect input and output
                    PrintStream output = new PrintStream(runOutFile);
                    System.setOut(output);
                    FileInputStream is = new FileInputStream(inFile);
                    System.setIn(is);

                    //run program
                    SolarStart.main(args);

                    //close files
                    output.close();
                    is.close();

                    //check answers--------------------------------------------------------------------------------
                    Scanner answer = new Scanner(Paths.get(answerFile));
                    Scanner result = new Scanner(Paths.get(runOutFile));

                    System.err.println("\n\n\n\n\n\n" +
                            "-----------------------------" + base + "-----------------------------");

                    //check for a mismatch pass
                    while (answer.hasNext() && result.hasNext()) {
                        String ansLine = answer.nextLine();
                        String resultLine = result.nextLine();

                        ansLine = cleanInput(answer, ansLine);
                        resultLine = cleanInput(result, resultLine);

                        if (!ansLine.equals(resultLine)) {
                            error = true;
                        }
                    }

                    if (answer.hasNext() || result.hasNext())
                        error = true;

                    //output pass, or the file with the problem lines
                    if (!error) {
                        System.err.println(ColorText.colorString("Passed", ColorText.Color.BLACK));
                    } else {
                        //check answers
                        answer = new Scanner(Paths.get(answerFile));
                        result = new Scanner(Paths.get(runOutFile));

                        while (answer.hasNext() && result.hasNext()) {
                            String ansLine = answer.nextLine();
                            String resultLine = result.nextLine();

                            ansLine = cleanInput(answer, ansLine);
                            resultLine = cleanInput(result, resultLine);

                            if (ansLine.equals(resultLine)) {
                                System.err.println(ColorText.colorString(resultLine, ColorText.Color.BLACK));
                            } else {
                                printError(resultLine, ansLine);
                            }
                        }

                        while (answer.hasNext()) {
                            String ansLine = answer.nextLine();
                            printError("", ansLine);
                        }

                        while (result.hasNext()) {
                            String resultLine = answer.nextLine();
                            printError(resultLine, "");
                        }

                    }
                }
            } catch (Exception e) {
                //Any error, use normal console input
                System.err.println("Error redirecting input. Continue with console input...");
                System.err.println("Error was: " + e.toString());
            }
        } else {
            //run normally
            SolarStart.main(args); //TODO change this to be your entry class
        }


    }

    public static void printError(String resultLine, String ansLine) {
        System.err.println(">>>>>>>Error>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        System.err.print("Got.....|");
        System.err.println(resultLine+"|");
        System.err.print("Needed..|");
        System.err.println(ansLine+"|");
    }

    public static String cleanInput(Scanner in, String line) {
        if (!CHECK_NEW_LINE) {
            while (line.trim().length() == 0 && in.hasNext())
                line = in.nextLine();
        }

        if (!CHECK_CAP) {
            line = line.toLowerCase();
        }

        if (!CHECK_LEFT_SPACING) {
            line = line.stripLeading();
        }

        if (!CHECK_RIGHT_SPACING) {
            line = line.stripTrailing();
        }

        return line;
    }
}
