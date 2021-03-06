open Jest;
open Expect;

describe("Api", () => {
  test("dummy", () => expect(true) |> toBe(true))
});

describe("Namer", () => {
  test("has term", () => {
    let expectedName = "word";
    let named = Namer.namer(
      ~term=expectedName,
      ~synonymes= [||],
      ~translations=[||],
      ~suggestions= [||]
    );

    expect(named.term) |> toEqual @@ Obj.magic(expectedName)
  })
});
