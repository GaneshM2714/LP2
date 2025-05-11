# Define possible performance levels for each criterion
QUALITY_LEVELS = ["Poor", "Fair", "Good", "Excellent"]
PRODUCTIVITY_LEVELS = ["Poor", "Fair", "Good", "Excellent"]
TEAMWORK_LEVELS = ["Poor", "Fair", "Good", "Excellent"]

# Define possible overall evaluation outcomes
OVERALL_EVALUATIONS = ["Unsatisfactory", "Needs Improvement", "Meets Expectations", "Meets or Exceeds Expectations", "Outstanding"]

def evaluate_employee_performance(quality_of_work, productivity, teamwork):
    """
    Evaluates employee performance based on predefined rules.

    Args:
        quality_of_work (str): Performance level for quality of work
                               (must be in QUALITY_LEVELS).
        productivity (str): Performance level for productivity
                            (must be in PRODUCTIVITY_LEVELS).
        teamwork (str): Performance level for teamwork and collaboration
                        (must be in TEAMWORK_LEVELS).

    Returns:
        str: The overall performance evaluation.
    """
    # Input validation (simplified)
    if quality_of_work not in QUALITY_LEVELS:
        return f"Invalid input for Quality of Work: {quality_of_work}"
    if productivity not in PRODUCTIVITY_LEVELS:
        return f"Invalid input for Productivity: {productivity}"
    if teamwork not in TEAMWORK_LEVELS:
        return f"Invalid input for Teamwork and Collaboration: {teamwork}"

    overall_evaluation = None

    # --- Rule Base ---

    # Rule 1: Outstanding
    if quality_of_work == "Excellent" and productivity == "Excellent" and teamwork == "Excellent":
        overall_evaluation = "Outstanding"

    # Rule 4: Unsatisfactory (Checking before Needs Improvement to catch the lowest performance)
    elif quality_of_work == "Poor" and productivity == "Poor":
         overall_evaluation = "Unsatisfactory"

    # Rule 3: Needs Improvement (Checking after Unsatisfactory)
    elif "Fair" in [quality_of_work, productivity, teamwork] or \
         "Poor" in [quality_of_work, productivity, teamwork]:
        # This rule applies if ANY of the criteria are Fair or Poor,
        # provided it's not the specific Unsatisfactory case already caught.
        if overall_evaluation is None: # Ensure it wasn't already set to Unsatisfactory
             overall_evaluation = "Needs Improvement"

    # Rule 2: Meets or Exceeds Expectations (Checking after lower performance rules)
    elif (quality_of_work in ["Excellent", "Good"]) and \
         (productivity in ["Excellent", "Good"]) and \
         (teamwork in ["Excellent", "Good"]):
         # This rule applies if ALL criteria are Good or Excellent,
         # and it wasn't the Outstanding case.
         if overall_evaluation is None: # Ensure it wasn't already set to Outstanding or lower
             overall_evaluation = "Meets or Exceeds Expectations"


    # Rule 5: Meets Expectations (Default if no other rule fires)
    if overall_evaluation is None:
        overall_evaluation = "Meets Expectations"

    return overall_evaluation

# --- Example Usage ---

# Example 1: An outstanding employee
employee1_quality = "Excellent"
employee1_productivity = "Excellent"
employee1_teamwork = "Excellent"
evaluation1 = evaluate_employee_performance(employee1_quality, employee1_productivity, employee1_teamwork)
print(f"Employee 1 Evaluation ({employee1_quality}, {employee1_productivity}, {employee1_teamwork}): {evaluation1}")

# Example 2: An employee who meets expectations
employee2_quality = "Good"
employee2_productivity = "Good"
employee2_teamwork = "Good"
evaluation2 = evaluate_employee_performance(employee2_quality, employee2_productivity, employee2_teamwork)
print(f"Employee 2 Evaluation ({employee2_quality}, {employee2_productivity}, {employee2_teamwork}): {evaluation2}")

# Example 3: An employee who needs improvement
employee3_quality = "Good"
employee3_productivity = "Fair"
employee3_teamwork = "Good"
evaluation3 = evaluate_employee_performance(employee3_quality, employee3_productivity, employee3_teamwork)
print(f"Employee 3 Evaluation ({employee3_quality}, {employee3_productivity}, {employee3_teamwork}): {evaluation3}")

# Example 4: An unsatisfactory employee
employee4_quality = "Poor"
employee4_productivity = "Poor"
employee4_teamwork = "Fair"
evaluation4 = evaluate_employee_performance(employee4_quality, employee4_productivity, employee4_teamwork)
print(f"Employee 4 Evaluation ({employee4_quality}, {employee4_productivity}, {employee4_teamwork}): {evaluation4}")

# Example 5: An employee who meets or exceeds expectations (not outstanding)
employee5_quality = "Excellent"
employee5_productivity = "Good"
employee5_teamwork = "Excellent"
evaluation5 = evaluate_employee_performance(employee5_quality, employee5_productivity, employee5_teamwork)
print(f"Employee 5 Evaluation ({employee5_quality}, {employee5_productivity}, {employee5_teamwork}): {evaluation5}")

# Example 6: Invalid input
employee6_quality = "Great"
employee6_productivity = "Good"
employee6_teamwork = "Good"
evaluation6 = evaluate_employee_performance(employee6_quality, employee6_productivity, employee6_teamwork)
print(f"Employee 6 Evaluation ({employee6_quality}, {employee6_productivity}, {employee6_teamwork}): {evaluation6}")