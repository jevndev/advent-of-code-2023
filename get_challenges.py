import datetime
import requests
import pathlib
from bs4 import BeautifulSoup


class AdventOfCodeChallenge:
    _START_YEAR = 2015
    _START_DATE = 1
    _END_DATE = 25

    def __init__(self, day: int, year: int) -> None:
        self._date = datetime.date(year=year, month=12, day=day)

        if year <= self._START_YEAR or not self._START_DATE <= day <= self._END_DATE:
            raise ValueError(f"Invalid Date passed {day}/{year}")

    @property
    def root_address(self) -> str:
        return f"https://adventofcode.com/{self._date.year}/day/{self._date.day}"

    @property
    def input_address(self) -> str:
        return self.root_address + "/input"

    @property
    def day(self) -> int:
        return self._date.day


def create_challenge_folder(
    root_directory: pathlib.Path, challenge: AdventOfCodeChallenge
) -> pathlib.Path:
    challenge_folder = root_directory / f"day_{challenge.day:02}"
    if challenge_folder.exists():
        return challenge_folder
    challenge_folder.mkdir()
    for part_name in ("part_1", "part_2"):
        part_folder = challenge_folder / part_name
        part_folder.mkdir()

    return challenge_folder


def get_instructions(challenge: AdventOfCodeChallenge):
    response = requests.get(challenge.root_address)
    if not response.ok:
        raise ConnectionError(response)
    page_content = BeautifulSoup(response.text, "html.parser")

    instruction_element = page_content.find("article", {"class", "day-desc"})
    instruction_title = instruction_element.find("h2")
    instruction_text = instruction_element.find_all("p")
    paragraph_delim = "\n\n"
    return f"{instruction_title.text}\n {paragraph_delim.join(paragraph.text for paragraph in instruction_text)}"


def get_input_file(challenge: AdventOfCodeChallenge):
    response = requests.get(challenge.input_address)
    print(response)
    if not response.ok:
        raise ConnectionError(response)

    page_content = BeautifulSoup(response.text, "html.parser")

    print(page_content.text)


def main():
    root_directory = pathlib.Path.cwd()
    current_year = datetime.datetime.now().year

    for day in range(1, 26):
        challenge = AdventOfCodeChallenge(day, current_year)
        challenge_folder = create_challenge_folder(root_directory, challenge)
        challenge_instructions = get_instructions(challenge)
        with open(challenge_folder / "instructions.txt", "w") as f:
            f.write(challenge_instructions)

    ...


if __name__ == "__main__":
    main()
