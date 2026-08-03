#import "/layout/fonts.typ": *

#let disclaimer(
  title: "",
  degree: "",
  author: "",
  submissionDate: datetime,
) = {
  set page(
    margin: (left: 30mm, right: 30mm, top: 40mm, bottom: 40mm),
    numbering: none,
    number-align: center,
  )

  set text(
    font: fonts.body,
    size: 12pt,
    lang: "en",
  )

  set par(leading: 1em)

  // --- Disclaimer ---
  v(65%)
  text(
    "I hereby confirm that the content of this "
      + degree
      + "'s thesis is my own work. I have documented all sources and materials used, relying exclusively on the cited sources. In particular, direct and indirect quotations are identified as such. I am aware that a violation of these provisions may result in the revocation of my academic degree, even retroactively. Furthermore, I certify that the electronic version is consistent with the printed copies.

      ",
  )

  v(15mm)
  grid(
    columns: 2,
    gutter: 2fr,
    "Leipzig, " + submissionDate.display("[day].[month].[year]"), author,
  )
}
