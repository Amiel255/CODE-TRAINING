public class MiniReceipt {
    public static void main(String[] args) {
        // 1. Header line
        System.out.println("********** RECEIPT **********");
        
        // 2. Receipt Items using \t for alignment and \" for quotes
        // \u20B1 is the escape sequence for the Peso sign so it renders properly
        System.out.println("Item: \"Pahinga\"\t\tPrice:\t₱120.00");
        System.out.println("Item: \"Tulog\"\t\tPrice:\t\u20B125.00");
        System.out.println("Item: \"USB Drive\"\tPrice:\t\u20B1500.00");
        
        // 3. Footer lines
        System.out.println("\nThank you for shopping!");
        System.out.println("*****************************");
    }
}
