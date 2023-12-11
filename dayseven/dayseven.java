import org.apache.commons.lang3.tuple.Pair;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.function.Function;
import java.util.stream.IntStream;

import static java.util.stream.Collectors.groupingBy;

public class AdventOfCodeDay7 {
    private static List<Character> cards = List.of('2', '3', '4', '5', 
'6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A');

    public static void main(String[] args) {
        List<Pair<String, Long>> handsToBids = new ArrayList<>();

        try (BufferedReader rd = new BufferedReader(new 
FileReader("input.txt"))) {
            String line;
            while ((line = rd.readLine()) != null) {
                String hand = line.split(" ")[0];
                Long bid = Long.parseLong(line.split(" ")[1]);
                handsToBids.add(Pair.of(hand, bid));
            }
        } catch (IOException ignored) {}

        List<Long> handsToRanks = handsToBids.stream()
                .collect(groupingBy(rankHandByType))
                .values()
                .stream()
                .flatMap(it -> it.stream().sorted(rankHandByValue()))
                .map(Pair::getRight)
                .toList();

        long sum = IntStream.range(0, handsToRanks.size())
                .mapToLong(i -> handsToRanks.get(i) * (i + 1))
                .sum();

        System.out.println("The sum is " + sum);

    }

    private static final Function<Pair<String, Long>, Integer> 
rankHandByType = card -> {
        String curr = card.getLeft();
        Map<Integer, Integer> cardOccurrences = new HashMap<>();
        curr.chars().forEach(val -> {
            if (cardOccurrences.containsKey(val))
                cardOccurrences.put(val, cardOccurrences.get(val) + 1);
            else
                cardOccurrences.put(val, 1);
        });

        if (cardOccurrences.containsValue(5))
            return 7;
        else if (cardOccurrences.containsValue(4))
            return 6;
        else if (cardOccurrences.containsValue(3) && 
cardOccurrences.containsValue(2))
            return 5;
        else if (cardOccurrences.containsValue(3))
            return 4;
        else if (cardOccurrences.containsValue(2) && new 
HashSet<>(cardOccurrences.values()).size() == cardOccurrences.size() - 1)
            return 3;
        else if (cardOccurrences.containsValue(2))
            return 2;
        else
            return 1;
    };

    private static Comparator<? super Pair<String, Long>> 
rankHandByValue() {
        return (l, r) -> {
            String lHand = l.getLeft();
            String rHand = r.getLeft();
            for (int i = 0; i < 5; ++i) {
                int lPower = cards.indexOf(lHand.charAt(i));
                int rPower = cards.indexOf(rHand.charAt(i));
                if (lPower < rPower)
                    return -1;
                else if (lPower > rPower)
                    return 1;
            }
            return 0;
        };
    }

}

