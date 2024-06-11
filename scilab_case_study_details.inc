<?php
// case study display completed proposals
function scilab_case_study_completed_proposals_all()
{
	$output = "";
	$query = db_select('case_study_proposal');
	$query->fields('case_study_proposal');
	$query->condition('approval_status', 3);
	$query->orderBy('actual_completion_date', 'DESC');
	//$query->condition('is_completed', 1);
	$result = $query->execute();
	
	//var_dump($case_study_abstract);die;
	if ($result->rowCount() == 0)
	{
		$output .= "There are no completed case studies currently. Click <a href='proposal'>here</a> to propose a case study.";

	} //$result->rowCount() == 0
	else
	{
		$output .= "Work has been completed for the following case studies. We welcome your contributions." . "<hr>";
		$preference_rows = array();
		$i = $result->rowCount();
		//var_dump($i);die;
		while ($row = $result->fetchObject())
		{
			$proposal_id = $row->id;
			$project_title = l($row->project_title, "case-study-project/case-study-run/" . $row->id);
			$year = date("Y", $row->actual_completion_date);
			$preference_rows[] = array(
				$i,
				$project_title,
				$row->contributor_name,
				$row->university,
				$year
			);
			$i--;
		} //$row = $result->fetchObject()
		$preference_header = array(
			'No',
			'Case Study Project',
			'Contributor Name',
			'University/ Institute',
			'Year of Completion'
		);
		$output .= theme('table', array(
			'header' => $preference_header,
			'rows' => $preference_rows
		));
	}
	return $output;
}
// case study display in progress proposals
function scilab_case_study_progress_all()
{
	$page_content = "";
	$query = db_select('case_study_proposal');
	$query->fields('case_study_proposal');
	$query->condition('approval_status', 1);
	$query->condition('is_completed', 0);
	$query->orderBy('approval_date', DESC);
	$result = $query->execute();
	if ($result->rowCount() == 0)
	{
		$page_content .= "There are no case studies in progress currently. Click <a href='proposal'>here</a> to propose a case study.";
	} //$result->rowCount() == 0
	else
	{
		$page_content .= "Work is in progress for the following case studies under case study Project<hr>";
		$preference_rows = array();
		$i = $result->rowCount();
		while ($row = $result->fetchObject())
		{
			$approval_date = date("Y", $row->approval_date);
			$preference_rows[] = array(
				$i,
				$row->project_title,
				$row->contributor_name,
				$row->university,
				$approval_date
			);
			$i--;
		} //$row = $result->fetchObject()
		$preference_header = array(
			'No',
			'Case Study Project',
			'Contributor Name',
			'Institute/ University',
			'Year'
		);
		$page_content .= theme('table', array(
			'header' => $preference_header,
			'rows' => $preference_rows
		));
	}
	return $page_content;
}
