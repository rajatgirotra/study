public record LPAStudent(String id, String name, String dateOfBirth, String classList) {
    // that's it.
    /* for each parameter (java calls it component), java does the following
    1) create a field with the same name as the component name
    2) make the field final and private
    3) generates toString()
    4) public getter method (accessor method) for each component; with the get or any other prefix.
    5) Records are immutable by design.
    6) There are no setters generated.
     */
}
