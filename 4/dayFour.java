import java.io.*;
import java.util.Arrays;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class aocDayFour {

    public static void main(String[] args) throws FileNotFoundException {

        File input = new File("aoc-2023/dayfour/input.txt");

        int totalWinnings = 0;

        try (BufferedReader inputReader = new BufferedReader(new FileReader(input))) {
            String line = inputReader.readLine();
            while (line != null) {

                String cardID = line.split(":")[0].trim();
                String rest = line.split(":")[1].trim();
                String winningNumbersString = rest.split("\\|")[0].trim().replaceAll(" +", " ");
                String cardNumbersString = rest.split("\\|")[1].trim().replaceAll(" +", " ");

                int cardIDValue = Integer.parseInt(cardID.replace("Card", "").replaceAll(" +", ""));
                Set<Integer> winningNumbers = Arrays.stream(winningNumbersString.split(" ")).map(Integer::parseInt).collect(Collectors.toSet());
                List<Integer> cardNumbers = Arrays.stream(cardNumbersString.split(" ")).map(Integer::parseInt).toList();

                int appearance = 0;
                for (int candidate: cardNumbers) {
                    if (winningNumbers.contains(candidate) && appearance ==0)
                        appearance = 1;
                    else if (winningNumbers.contains(candidate))
                        appearance *= 2;
                }
                if (appearance != 0)
                    totalWinnings += appearance;

                line = inputReader.readLine();
            }


        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        System.out.println("Total winnigs: " + totalWinnings);

    }

}
