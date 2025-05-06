import difflib
class HelpDesk:
    def __init__(self):
        self.issues = {
            "Password Reset": {
                "symptoms": {
                    "cannot login": 4,
                    "forgot password": 4,
                    "account locked": 3,
                    "error message": 2
                },
                "action": "Please visit our portal website for customer management and reset your password from there.",
                "priority": "high"
            },
            "Network Issues": {
                "symptoms": {
                    "no internet": 4,
                    "slow connection": 3,
                    "disconnected": 2,
                    "unable to access": 2,
                    "error message": 2
                },
                "action": "Please check the Internet. Restart the service or shift to another connection.",
                "priority": "low"
            },
            "Software Crash": {
                "symptoms": {
                    "unable to access": 4,
                    "server down": 3,
                    "cannot respond": 3,
                    "disconnected": 1
                },
                "action": "Try restarting the application, updating the software or try after some time",
                "priority": "medium"
            },
            "Printer Issue": {
                "symptoms": {
                    "cannot print": 4,  
                    "printer is busy": 4,
                    "ctrl+p not responding": 1,
                },
                "action": "Seems like Printer issue. Please try restarting and properly connecting your printer",
                "priority": "low"
            },
            "Email Access": {
                "symptoms": {
                    "cannot send email": 4,
                    "email not found": 4,
                    "server down": 2,
                    "disconnected": 1
                },
                "action": "Verify email settings and privileges, try contacting IT support.",
                "priority": "high"
            },
            "Hardware Failure": {
                "symptoms": {
                    "computer wont start": 4,
                    "bluescreen": 3,
                    "cannot reboot": 3,
                    "unable to access": 1,
                    "error message": 2
                },
                "action": "Run diagnostics, check the hardware, contact the IT for repair.",
                "priority": "medium"
            },
            "Slow Performance": {
                "symptoms": {
                    "slow loading": 4,
                    "slow computer": 3,
                    "lagging": 3,
                    "cannot reboot": 1
                },
                "action": "Might be memory management issues due to overloading, try closing unnecessary background applications",
                "priority": "high"
            }
        }
    
    def is_similar(self, user_issue, symptom):
        """
        Check if two strings are similar based on difflib's similarity ratio.
        Returns True if similarity ratio is >= max_similarity_threshold.
        """
        # Case-insensitive comparison
        user_issue = user_issue.lower()
        symptom = symptom.lower()
        similarity = difflib.SequenceMatcher(None, user_issue, symptom).ratio()
        return similarity >= 0.6

    def get_symptoms(self):
        symptoms = input("Enter the symptoms you are facing (comma-separated): ").strip()
        if not symptoms:
            print("No symptoms entered. Please try again.")
            return []
        # Split and clean tokens
        tokens = [token.strip().lower() for token in symptoms.split(',')]
        return tokens

    def show(self, issues):
        if not issues:
            print("No potential issues found with the provided symptoms.")
            return
        print("Here are all possible potential issues (sorted by confidence):")
        issues.sort(key=lambda x: x['confidence'], reverse=True)
        for issue in issues:
            print(f"Issue: {issue['issue']}")
            print(f"Confidence: {issue['confidence']:.2%}")
            print(f"Action: {issue['action']}")
            print(f"Priority: {issue['priority']}")
            print()

    def res(self, symptoms, confidence_threshold=0.2):
        if not symptoms:
            return []
        issues = []
        for issue, info in self.issues.items():
            total_weight = 0
            matched_weight = 0
            for sym, wt in info['symptoms'].items():
                total_weight += wt
                if any(self.is_similar(user_sym, sym) for user_sym in symptoms):
                    matched_weight += wt

            confidence = matched_weight / total_weight if total_weight != 0 else 0

            if confidence >= confidence_threshold:
                issues.append({
                    "issue": issue,
                    "confidence": confidence,
                    "action": info['action'],
                    "priority": info['priority']
                })
        self.show(issues)
        return issues

if __name__ == "__main__":
    sys = HelpDesk()
    syms = sys.get_symptoms()
    sys.res(syms)