import org.apache.commons.lang3.tuple.Pair;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class AdventOfCodeDay8 {

    public static void main(String[] args) {
        int[] instructions = {0};
        List<Pair<String, Pair<String, String>>> nodes = new 
ArrayList<>();

        try (BufferedReader rd = new BufferedReader(new 
FileReader("input.txt"))) {
            String line;
            boolean firstLine = true;
            while ((line = rd.readLine()) != null) {
                if (!line.isBlank() && firstLine) {
                    firstLine = false;
                    instructions = line.chars().map(c -> {
                        if (c == 'L')
                            return 0;
                        else
                            return 1;
                    }).toArray();
                } else if (!line.isBlank()) {
                    String node = line.split("=")[0].trim();
                    String paths = line.split("=")[1].trim().replace("(", 
"").replace(")", "");
                    String firstPath = paths.split(",")[0].trim();
                    String secondPath = paths.split(",")[1].trim();
                    nodes.add(Pair.of(node, Pair.of(firstPath, 
secondPath)));
                }
            }
        } catch (IOException ignored) {}

        String currentNode = "AAA";
        int steps = 0;
        while (!currentNode.equals("ZZZ")) {
            for (int instruction : instructions) {
                final String current = currentNode;
                Pair<String, String> paths = nodes.stream().filter(p -> 
p.getLeft().equalsIgnoreCase(current)).map(Pair::getRight).toList().get(0);
                if (instruction == 0) {
                    currentNode = paths.getLeft();
                } else {
                    currentNode = paths.getRight();
                }
                ++steps;
            }
        }

        System.out.println("Total number of steps: " + steps);

    }
}

