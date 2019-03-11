class Solution {
    public int bagOfTokensScore(int[] tokens, int P) {
        if (tokens.length == 0) {
            return 0;
        }
        Arrays.sort(tokens);
        int lhs = 0, rhs = tokens.length - 1, score = 0;
        while (lhs <= rhs) {
            if (P >= tokens[lhs]) {
                P -= tokens[lhs];
                score++;
                lhs++;
            } else if (score > 0 && lhs != rhs) {
                P += tokens[rhs];
                score--;
                rhs--;
            } else {
                break;
            }
        }
        return score;
    }
}
