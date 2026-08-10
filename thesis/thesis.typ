#import "/layout/thesis_template.typ": *
#import "/metadata.typ": *
#import "/content/abbreviations.typ": abbreviations

#set document(title: titleEnglish, author: author)

#show: thesis.with(
  title: titleEnglish,
  titleGerman: titleGerman,
  degree: degree,
  program: program,
  examiner: examiner,
  supervisors: supervisors,
  author: author,
  startDate: startDate,
  submissionDate: submissionDate,
  abstract_en: include "/content/abstract_en.typ",
  abstract_de: include "/content/abstract_de.typ",
  acknowledgement: include "/content/acknowledgement.typ",
  transparency_ai_tools: include "/content/transparency_ai_tools.typ",
  abbreviations_list: abbreviations,
)

#include "/content/1_introduction.typ"
#include "/content/2_background.typ"
#include "/content/3_existing_solutions.typ"
#include "/content/4_requirements.typ"
#include "/content/5_implementation.typ"
#include "/content/6_evaluation.typ"
#include "/content/7_summary.typ"
