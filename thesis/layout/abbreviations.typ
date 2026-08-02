#import "/layout/fonts.typ": *

#let abbreviations(abbreviations_list) = {
  set text(
    font: fonts.body,
    size: 12pt,
    lang: "en",
  )

  table(
    columns: (25%, 75%),
    align: (left, left),
    stroke: none,
    inset: (top: 6pt, bottom: 6pt),
    table.header(text(weight: "bold", [Abbreviation]), text(weight: "bold", [Description])),
    ..for (abb, desc) in abbreviations_list {
      ([#abb], [#desc])
    },
  )
}
