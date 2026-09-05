#let fr_counter = counter("fr")
#let qa_counter = counter("qa")
#let const_counter = counter("const")

#let FR(headline, description) = [
  #fr_counter.step()
  #context [
    #set align(left)
    #let key = "fr-" + lower(headline.replace(" ", "-"))
    // Have to use figures because we cannot directly use labels on grids
    #figure(
      {
        set text(
          font: "New Computer Modern",
          size: 12pt,
          lang: "en",
        )
        grid(
          columns: (auto, 1fr),
          column-gutter: 3mm,
          align: (right, left),
          "FR" + context fr_counter.display(), strong(headline) + ": " + description,
        )
      },
      kind: "FR",
      supplement: "FR",
    )
    #label(key)
  ]
]

#let QA(headline, description, ckey: none) = [
  #qa_counter.step()
  #context [
    #set align(left)
    #let key = ckey
    #if ckey == none {
      key = "qa-" + lower(headline.replace(" ", "-"))
    }
    // Have to use figures because we cannot directly use labels on grids
    #figure(
      {
        set text(
          font: "New Computer Modern",
          size: 12pt,
          lang: "en",
        )
        grid(
          columns: (auto, 1fr),
          column-gutter: 3mm,
          align: (right, left),
          "QA" + context qa_counter.display(), strong(headline) + ": " + description,
        )
      },
      kind: "QA",
      supplement: "QA",
    )
    #label(key)
  ]
]


#let C(headline, description) = [
  #const_counter.step()
  #context [
    #set align(left)
    #let key = "c-" + lower(headline.replace(" ", "-"))
    // Have to use figures because we cannot directly use labels on grids
    #figure(
      {
        set text(
          font: "New Computer Modern",
          size: 12pt,
          lang: "en",
        )
        grid(
          columns: (auto, 1fr),
          column-gutter: 3mm,
          align: (right, left),
          "C" + context const_counter.display(), strong(headline) + ": " + description,
        )
      },
      kind: "C",
      supplement: "C",
    )
    #label(key)
  ]
]

